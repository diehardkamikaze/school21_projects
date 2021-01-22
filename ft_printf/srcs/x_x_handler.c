/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_x_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:08:08 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 14:23:11 by mchau            ###   ########.fr       */
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
	return (va_arg(args, int));
}

int			print_ox(t_params *t, char flag, char from)
{
	char	x;

	x = 23 + from;
	if ((t->flags & PF_GRILL) && flag)
	{
		write(1, "0", 1);
		write(1, &x, 1);
	}
	return (1);
}

int			x_handler(t_params *t, va_list args)
{
//	int					result_count;
	unsigned long long	x;

	x = inner_long_handler_x(t->length, args);
	return (x);
}

int			x_upper_handler(t_params *t, va_list args)
{
//	int					result_count;
	unsigned long long	x;

	x = inner_long_handler_x(t->length, args);
	return (x);
}
