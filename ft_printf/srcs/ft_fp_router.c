/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fp_router.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:11:57 by mchau             #+#    #+#             */
/*   Updated: 2021/02/25 12:13:34 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//just debug function
void	print_bits(unsigned long long val, int nbits)
{
	if (nbits != 0)
	{
		print_bits(val >> 1, nbits - 1);
		ft_printf("%lld", val & 1);
	}
}

//just debug function
void	pretty_print(t_fpbits *t)
{
	ft_printf("sign: %hhd\n", t->sign);
	ft_printf("yexp: %d : ", t->exp);
	print_bits(t->exp, 11);
	ft_printf("\nmantissa: %lu : 1/0 ", t->mantissa);
	print_bits(t->mantissa, 52);
}

int		nan_inf_handler(t_params *t)
{
	t_fpbits tmp;
	char *s;
	char *value;

	tmp = *(t->fp);
	if (tmp.mantissa == 0)
	{
		value = "inf";
		if (tmp.sign == 1)
			value = "-inf";
		else
			if (t->flags & PF_PLUS)
				value = "+inf";
			else if (t->flags & PF_SPACE)
				value = " inf";
	}
	else
		value = "nan";
	s = "%*s";
	if (t->flags & PF_MINUS)
		s = "%-*s";
	return (ft_printf(s, t->width, value));
}

void	encode_double(double num, t_fpbits *t)
{
	unsigned long bits;

	bits = *((unsigned long *)(&num));
	t->sign = bits >> 63 ? 1 : 0;
	t->exp = ((bits >> 52) & ((1 << 11) - 1)) - 1023;
	t->mantissa = bits & (((unsigned long)1 << 52) - 1);
}

int		ft_fp_router(char specific, t_params *t, va_list args)
{
	t_fpbits	tmp;

	encode_double(va_arg(args, double), &tmp);
	t->fp = &tmp;
//	pretty_print(&tmp);
	if (tmp.exp == 1024)
		return (nan_inf_handler(t));
	if (t->precision < 0)
		t->precision = 6;
	if (specific == 'g')
	{
		tmp.ignore_zeros = 0; //may be del that
		if (t->precision == 0)
			t->precision = 1;
		if (t->precision > tmp.exp && tmp.exp >= -4)
		{
			specific = 'f';
			t->precision = t->precision - tmp.exp - 1;
		}
		else
		{
			specific = 'e';
			t->precision -= 1;
		}
	}
	/*if (specific == 'e')
		return (e_handler(t, 0));*/ 
	if (specific == 'f')
		return (f_handler(t, 0));
	return (-1);
}
