/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:18:02 by mchau             #+#    #+#             */
/*   Updated: 2021/02/26 17:31:36 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//del that
void ft_debug(char *d, long value) {
	ft_printf("\n");
	ft_printf(d, value);
	ft_printf("\n");
}

void	print_fraction(t_bigint *fract, int precision, int expfract)
{
	int		leading_zeros;
	int		length;
	char	c;

	length = fract->dig_num;
	leading_zeros = expfract - length;
	while (precision > 0 && leading_zeros > 0)
	{
		write(1, "0", 1);
		precision--;
		leading_zeros--;
	}
	while (precision && length > 0)
	{
		c = '0' + (fract->digits[(length-1) / 9] / ft_binpow(10, (length - 1) % 9)) % 10;
		write(1, &c, 1);
		length--;
		precision--;
	}
	while (precision-- > 0)
		write(1, "0", 1);
}

int	f_handler(t_params *t, va_list args)
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
	if (0 <= t->precision && t->precision < expfract)
	{
		int m = 0;
		// zdes moject bit owibka pri precision == 0 i fractionpart = 0
		if (t->precision == 0 && expfract == fractionpart->dig_num && !(mantissafract & (mantissafract - 1)))
			if(integerpart->digits[0] % 2 == 0)
				m = 0;
			else
				m = 1;
		else
				m = bigint_round_from(fractionpart, expfract - t->precision, expfract);
		bigint_summ_short(integerpart, m);
	}
	char fill = ' ';
	char sign = 0;
	int result_len = 0;
	if (t->fp->sign && (sign = '-'))
		result_len++;
	else if (t->flags & PF_PLUS && (sign = '+'))
		result_len++;
	else if (t->flags & PF_SPACE && (sign = ' '))
		result_len++;
	result_len += integerpart->dig_num + t->precision;
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
	bigint_print(integerpart);
	if (t->flags & PF_GRILL || t->precision != 0)
		ft_printf(".");
	print_fraction(fractionpart, t->precision, expfract);
	if ((PF_MINUS & t->flags))
		print_nchr(fill, t->width);
	return (result_len + t->width);
}
