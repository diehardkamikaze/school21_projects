/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_handlers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:58:33 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 15:48:28 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	spec_handler(char flag, t_params *t)
{
	t->specific = &error_log;
	if (t->precision < 0)
		t->dot = 0;
	if (t->width < 0 && (t->minus = 1))
		t->width = (-1) * t->width;
	if (t->minus == 1)
		t->zero = 0;
	if (flag == 's')
		t->specific = &s_handler;
	if (flag == 'c')
		t->specific = &c_handler;
	if (flag == '%')
		t->specific = &percent_handler;
	if (flag == 'd' || flag == 'i')
		t->specific = &d_i_handler;
	if (flag == 'p')
		t->specific = &p_handler;
	if (flag == 'u')
		t->specific = &u_handler;
	if (flag == 'x')
		t->specific = &x_handler;
	if (flag == 'X')
		t->specific = &x_upper_handler;
}

int		flag_handler(char flag, t_params *t)
{
	if (flag == '0')
		t->zero = 1;
	if (flag == '-')
		t->minus = 1;
	return (1);
}
