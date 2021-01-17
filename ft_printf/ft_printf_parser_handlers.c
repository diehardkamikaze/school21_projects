/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_handlers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:58:33 by mchau             #+#    #+#             */
/*   Updated: 2021/01/15 19:52:56 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int spec_handler(char flag, t_params *t)
{
	int result;
	result = 1;
	if (t->zero == 1 && t->minus == 1)
		return (error_log("0", "results in undefined behavior with 'c'\n"));
	if(t->width < 0)
	{
		t->width = t->width * -1;
		t->minus = 1;
		t->zero = 0;
	}
	if (flag == 's')
		t->specific = &s_handler;
	if (flag == 'c')
		t->specific = &c_handler;
	if (flag == '2')
		t->specific = (void *)(long)flag;
	/*if (flag == 's')
		t->specific = &s_handler;
	if (flag == 'p')
		t->specific = &p_handler;
	if (flag == 'd' || flag == 'i')
		t->specific = &di_handler;
	if (flag == 'u')
		t->specific = &u_handler;
	if (flag == 'x')
		t->specific = &x_handler;
	if (flag == 'X')
		t->specific = &big_x_handler; */
	return (result);
}

int	flag_handler(char flag, t_params *t)
{
	if (flag == '0')
		t->zero = 1;
	if(flag == '-')
		t->minus = 1;
	return (1);
}
