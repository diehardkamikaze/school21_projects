/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:02:07 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 17:36:38 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		c_handler(t_params *t, va_list arg)
{
	char	c;
	int		result_count;
	int		n;

	c = (char)va_arg(arg, int);
	n = t->width > 1 ? t->width - 1 : 0;
	result_count = 1;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, &c, 1);
	if (t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int		s_handler(t_params *t, va_list arg)
{
	char	*s;
	int		result_count;
	int		n;

	result_count = 0;
	s = (char *)va_arg(arg, void *);
	if (s == 0)
		s = "(null)";
	while (s[result_count] != 0)
		result_count++;
	if (t->dot && t->precision >= 0 && result_count > t->precision)
		result_count = t->precision;
	n = t->width > result_count ? t->width - result_count : 0;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, s, result_count);
	if (t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int		percent_handler(t_params *t, va_list arg)
{
	int		result_count;
	char	fill;
	int		n;

	if (arg)
		result_count = 1;
	result_count = 1;
	fill = t->zero ? '0' : ' ';
	n = t->width > 1 ? t->width - 1 : 0;
	if (!t->minus)
		print_nchr(fill, n);
	write(1, "%", 1);
	if (t->minus)
		print_nchr(fill, n);
	return (n + result_count);
}

void	inner_handler(t_params *t, int np, int is_negative, char fill)
{
	if (is_negative && fill == '0')
		write(1, "-", 1);
	if (!t->minus)
		print_nchr(fill, t->width);
	if (is_negative && !(fill == '0'))
		write(1, "-", 1);
	print_nchr('0', np);
}

int		d_i_handler(t_params *t, va_list arg)
{
	long	d;
	int		result_count;
	int		is_negative;
	int		fill;
	int		np;

	is_negative = 0;
	d = (long)va_arg(arg, int);
	if (d < 0 && (is_negative = 1))
		d = d * (-1);
	if ((fill = ' ') && t->zero && !t->dot)
		fill = '0';
	result_count = ft_number_len(d, 10);
	if (!(np = 0) && t->dot && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && d == 0)
		result_count--;
	t->width = (t->width > np + result_count + is_negative) ?
		t->width - np - result_count - is_negative : 0;
	inner_handler(t, np, is_negative, fill);
	if (result_count)
		ft_putnbr_positive(d, 10, 'a');
	if (t->minus)
		print_nchr(fill, t->width);
	return (np + t->width + is_negative + result_count);
}
