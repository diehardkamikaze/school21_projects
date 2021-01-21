/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:48:21 by mchau             #+#    #+#             */
/*   Updated: 2021/01/21 16:56:10 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent_handler(t_params *t, va_list arg)
{
	int		result_count;
	char	fill;
	int		n;

	if (arg)
		result_count = 1;
	result_count = 1;
	fill = (t->flags & PF_ZERO) ? '0' : ' ';
	n = t->width > 1 ? t->width - 1 : 0;
	if (!(t->flags & PF_MINUS))
		print_nchr(fill, n);
	write(1, "%", 1);
	if (t->flags & PF_MINUS)
		print_nchr(fill, n);
	return (n + result_count);
}
