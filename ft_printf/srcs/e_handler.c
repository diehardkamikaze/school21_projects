/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:18:02 by mchau             #+#    #+#             */
/*   Updated: 2021/02/26 17:07:38 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_number(t_bigint *part, int numer)
{
	unsigned long value = part->digits[(numer - 1) / 9];
	numer = (numer - 1) % 9;
	while(numer--)
		value /= 10;
	return value % 10;
}

void	print_e(int expfract, int e, t_bigint *integerpart, t_bigint *fractionpart, t_params *t)
{
	char firstdig = '0';
	if (e >= 0)
	{
		firstdig += get_number(integerpart, integerpart->dig_num);
		integerpart->dig_num--;
	}
	else if (e < 0)
	{
		firstdig += get_number(fractionpart, fractionpart->dig_num);
		fractionpart->dig_num--;
		integerpart->dig_num--;
	}
	ft_printf("%c", firstdig);
	if (t->flags & PF_GRILL || (t->precision != 0 && !(t->fp->isignore && integerpart->dig_num + fractionpart->dig_num == 0)))
		ft_printf(".");
	while (t->precision && integerpart->dig_num)
	{
		int c = '0' + get_number(integerpart, integerpart->dig_num);
		write(1, &c, 1);
		integerpart->dig_num--;
		t->precision--;
	}
	//zabil pro leading zeros
	int leadingzeros = 0;
	if(e >= 0)
		leadingzeros = expfract - fractionpart->dig_num;
//	ft_printf("idd\n%d\n",leadingzeros);
	while (t->precision && leadingzeros)
	{
		write(1, "0", 1);
		t->precision--;
		leadingzeros--;
	}
	while (t->precision && fractionpart->dig_num)
	{
		int c = '0' + get_number(fractionpart, fractionpart->dig_num);
		write(1, &c, 1);
		fractionpart->dig_num--;
		t->precision--;
	}
	if (t->flags & PF_GRILL || !(t->fp->isignore))
		while (t->precision--)
			write(1, "0", 1);
	ft_printf("e%+03d", e);

}

int		e_handler(t_params *t, va_list args)
{
	int			expint = 0;
	int			expfract = 0;
	unsigned long			mantissaint = 0;
	unsigned long			mantissafract = 0;
	int			mantissalen;
	t_bigint	*integerpart;
	t_bigint	*fractionpart;

	mantissalen = 52;
	if (!args && t->fp->exp == -1023)
		t->fp->exp = -1022; // ni na chto ne povlyaet?
	else
		t->fp->mantissa = t->fp->mantissa + ((unsigned long)1 << mantissalen);
	if (t->fp->exp >= 52)
	{
		mantissaint = t->fp->mantissa;
		expint = t->fp->exp - mantissalen;
	}
	else if (t->fp->exp < 0)
	{
		mantissafract = t->fp->mantissa;
		expfract = t->fp->exp * - 1 + mantissalen;
	}
	else
	{
		expfract = mantissalen - t->fp->exp;
		mantissafract = t->fp->mantissa & (((unsigned long)1 << expfract) - 1);
		mantissaint = t->fp->mantissa >> expfract;
	}
	integerpart = bigint_constructor(mantissaint);
	fractionpart = bigint_constructor(mantissafract);
	divide_and_rule(integerpart, 2, expint);
	if (fractionpart != 0)
		divide_and_rule(fractionpart, 5, expfract);
	int e = 0;
	//другое округление:
	//это все случай e > 0
	if (mantissaint)
	{
		if (integerpart->dig_num - t->precision > 1)
			//3 параметр конечно абсолютно кривой, нужно продумать другую архитектуру, он здесь не нужен
			bigint_round_from(integerpart, integerpart->dig_num - t->precision - 1, integerpart->dig_num + 1);
		else
		{
			int tmpprecision = t->precision - integerpart->dig_num + 1;
			//precision нам еще понадобится, используй другую переменную
			if (0 <= tmpprecision && tmpprecision < expfract)
			{
				int m = 0;
				// zdes moject bit owibka pri precision == 0 i fractionpart = 0
				if (tmpprecision == 0 && expfract == fractionpart->dig_num && !(mantissafract & (mantissafract - 1)))
					if(integerpart->digits[0] % 2 == 0)
						m = 0;
					else
						m = 1;
				else
					m = bigint_round_from(fractionpart, expfract - tmpprecision, expfract);
				bigint_summ_short(integerpart, m);
			}
		}
		e = integerpart->dig_num - 1;//считать над после округления
	}
	else if (mantissafract) //e < 0
	{
		int m = 0;
		m = bigint_round_from(fractionpart, fractionpart->dig_num - t->precision - 1, expfract);
		bigint_summ_short(integerpart, m);
		e = fractionpart->dig_num - expfract - 1;
		if (integerpart->digits[0])
			e = 0;
	}
	char fill = ' ';
	char sign = 0;
	int result_len = 4;
	if (e > 99 || e < -99)
		result_len++;
	if (t->fp->sign && (sign = '-'))
		result_len++;
	else if (t->flags & PF_PLUS && (sign = '+'))
		result_len++;
	else if (t->flags & PF_SPACE && (sign = ' '))
		result_len++;
	result_len += 1 + t->precision;
	if (t->flags & PF_GRILL || t->precision != 0)
		result_len++;
	if (PF_ZERO & t->flags)
	{
		fill = '0';
		if (sign)
			write(1, &sign, 1);
	}
	t->width = t->width - result_len > 0 ? t->width - result_len : 0;
	if (!(PF_MINUS & t->flags))
		print_nchr(fill, t->width);
	if (sign && fill != '0')
		 write(1, &sign, 1);
	print_e(expfract, e, integerpart, fractionpart, t);
	if ((PF_MINUS & t->flags))
		print_nchr(fill, t->width);
	return (result_len + t->width);
}
