/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_x_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:08:08 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 17:14:17 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	inner_long_handler_x(unsigned char length, va_list args)
{
	if (length == 'h')
		return ((unsigned short int)va_arg(args, int));
	if (length == 'h' + 'h')
		return ((unsigned char)va_arg(args, int));
	if (length == 'l')
		return (va_arg(args, unsigned long int));
	if (length == 'l' + 'l')
		return (va_arg(args, unsigned long long int));
	return (va_arg(args, unsigned int));
}

int			print_ox(t_params *t, char flag, int grill,\
		unsigned long long num)
{
	if (num && grill && (t->flags & PF_GRILL) && flag)
	{
		write(1, "0x", 2);
	}
	return (1);
}

int			print_ox_big(t_params *t, char flag, int grill,\
		unsigned long long num)
{
	if (num && grill && (t->flags & PF_GRILL) && flag)
	{
		write(1, "0X", 2);
	}
	return (1);
}

int			x_handler(t_params *t, va_list args)
{
	int					result_count;
	unsigned long long	x;
	char				fill;
	int					np;
	int					grill;

	np = 0;
	grill = t->flags & PF_GRILL ? 2 : 0;
	fill = t->flags & PF_ZERO ? '0' : ' ';
	x = inner_long_handler_x(t->length, args);
	result_count = ft_number_len(x, 16);
	if (t->precision >= 0 && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (x == 0 && !(grill = 0) && t->precision == 0)
		result_count--;
	t->width = t->width > np + grill + result_count ?\
		t->width - np - grill - result_count : 0;
	if (print_ox(t, fill == '0', grill, x) && !(t->flags & PF_MINUS))
		print_nchr(fill, t->width);
	print_ox(t, !(fill == '0'), grill, x);
	if (result_count && print_nchr('0', np))
		ft_putnbr_positive(x, 16, 'a');
	if (t->flags & PF_MINUS)
		print_nchr(' ', t->width);
	return (result_count + t->width + np + grill);
}

int			x_upper_handler(t_params *t, va_list args)
{
	int					result_count;
	unsigned long long	x;
	char				fill;
	int					np;
	int					grill;

	np = 0;
	grill = t->flags & PF_GRILL ? 2 : 0;
	fill = t->flags & PF_ZERO ? '0' : ' ';
	x = inner_long_handler_x(t->length, args);
	result_count = ft_number_len(x, 16);
	if (t->precision >= 0 && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (x == 0 && !(grill = 0) && t->precision == 0)
		result_count--;
	t->width = t->width > np + grill + result_count ?\
		t->width - np - grill - result_count : 0;
	if (print_ox_big(t, fill == '0', grill, x) && !(t->flags & PF_MINUS))
		print_nchr(fill, t->width);
	print_ox_big(t, !(fill == '0'), grill, x);
	if (result_count && print_nchr('0', np))
		ft_putnbr_positive(x, 16, 'A');
	if (t->flags & PF_MINUS)
		print_nchr(' ', t->width);
	return (result_count + t->width + np + grill);
}
