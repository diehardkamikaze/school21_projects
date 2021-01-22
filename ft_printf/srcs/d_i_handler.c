/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_i_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:05:01 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 17:02:28 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	inner_long_handler(unsigned char length, va_list args)
{
	if (length == 'h')
		return ((short int)va_arg(args, int));
	if (length == 'h' + 'h')
		return ((char)va_arg(args, int));
	if (length == 'l')
		return (va_arg(args, long int));
	if (length == 'l' + 'l')
		return (va_arg(args, long long int));
	return (va_arg(args, int));
}

int			get_sign(char flags, char *symb)
{
	*symb = 0;
	if (flags & PF_SPACE)
		*symb = ' ';
	if (flags & PF_PLUS)
		*symb = '+';
	return (1);
}

int			inner_handler(t_params *t, char sign, char fill,\
		unsigned long long d)
{
	int	result_count;
	int	is_signed;
	int	np;

	np = 0;
	is_signed = sign ? 1 : 0;
	result_count = ft_number_len(d, 10);
	if (t->precision >= 0 && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->precision == 0 && d == 0)
		result_count--;
	t->width = (t->width > np + result_count + is_signed) ?
		t->width - np - result_count - is_signed : 0;
	if (is_signed && fill == '0')
		write(1, &sign, 1);
	if (!(t->flags & PF_MINUS))
		print_nchr(fill, t->width);
	if (is_signed && !(fill == '0'))
		write(1, &sign, 1);
	if (result_count && print_nchr('0', np))
		ft_putnbr_positive(d, 10, 'a');
	if ((t->flags & PF_MINUS))
		print_nchr(' ', t->width);
	return (result_count + t->width + np + is_signed);
}

int			d_i_handler(t_params *t, va_list arg)
{
	long long			temp;
	unsigned long long	d;
	char				sign;
	char				fill;

	temp = inner_long_handler(t->length, arg);
	d = temp;
	if (get_sign(t->flags, &sign) && temp < 0 && (sign = '-'))
		d = temp * -1;
	fill = t->flags & PF_ZERO ? '0' : ' ';
	return (inner_handler(t, sign, fill, d));
}
