/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_handlers2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:11:56 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 15:13:08 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		p_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned long	p;
	int				n;

	p = va_arg(args, unsigned long);
	result_count = 2 + ft_number_len(p, 16);
	if (t->dot && t->precision == 0 && p == 0)
		result_count--;
	n = t->width > result_count ? t->width - result_count : 0;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, "0x", 2);
	if (result_count > 2)
		ft_putnbr_positive(p, 16, 'a');
	if (t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int		u_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	u;
	int				np;
	int				n;
	char			fill;

	u = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(u, 10);
	np = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && u == 0)
		result_count--;
	if (!(n = 0) && (t->width > np + result_count))
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(u, 10, 'a');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}

int		x_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	x;
	int				np;
	int				n;
	char			fill;

	x = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(x, 16);
	np = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && x == 0)
		result_count--;
	if (!(n = 0) && (t->width > np + result_count))
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(x, 16, 'a');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}

int		x_upper_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	x;
	int				np;
	int				n;
	char			fill;

	x = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(x, 16);
	np = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && x == 0)
		result_count--;
	if (!(n = 0) && (t->width > np + result_count))
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(x, 16, 'A');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}
