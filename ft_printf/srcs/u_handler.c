/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:44:29 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 14:56:35 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	inner_long_handler_u(unsigned char length, va_list args)
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

int			u_handler(t_params *t, va_list args)
{
	int					result_count;
	unsigned long long	u;
	char				fill;
	int					np;
	int					n;

	u = inner_long_handler_u(t->length, args);
	if ((fill = ' ') && t->flags & PF_ZERO)
		fill = '0';
	result_count = ft_number_len(u, 10);
	np = 0;
	if (t->precision >= 0 && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->precision == 0 && u == 0)
		result_count--;
	if (!(n = 0) && (t->width > np + result_count))
		n = t->width - np - result_count;
	if (!(t->flags & PF_MINUS))
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(u, 10, 'a');
	if (t->flags & PF_MINUS)
		print_nchr(fill, n);
	return (result_count + np + n);
}
