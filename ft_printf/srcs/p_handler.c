/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:31:48 by mchau             #+#    #+#             */
/*   Updated: 2021/01/21 18:04:10 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		p_handler(t_params *t, va_list args)
{
	int					result_count;
	unsigned long long	p;
	int					n;

	p = (unsigned long long)va_arg(args, void *);
	result_count = 2 + ft_number_len(p, 16);
	if (t->precision == 0 && p == 0)
		result_count--;
	n = t->width > result_count ? t->width - result_count : 0;
	if (!(t->flags & PF_MINUS))
		print_nchr(' ', n);
	write(1, "0x", 2);
	if (result_count > 2)
		ft_putnbr_positive(p, 16, 'a');
	if (t->flags & PF_MINUS)
		print_nchr(' ', n);
	return (result_count + n);
}
