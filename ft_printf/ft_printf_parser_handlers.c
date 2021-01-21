/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_handlers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:58:33 by mchau             #+#    #+#             */
/*   Updated: 2021/01/20 14:37:57 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_preprocessor(t_params *t)
{
	if (t->width < 0)
	{
		t->width = -1 * t->width;
		t->flag = t->flag | PF_MINUS;
	}
	if (t->flag && PF_MINUS)
        t->zero = 0;
}

int		ft_router(char flag, t_params *t, va_list args, int len)
{
	if (flag == 's')
		return (s_handler(t, args));
	if (flag == 'c')
		return (c_handler(t, args));
	if (flag == '%')
		return (percent_handler(t, args));
	if (flag == 'd' || flag == 'i')
		return (d_i_handler(t, args));
	if (flag == 'p')
		return (p_handler(t, args));
	if (flag == 'u')
		return (u_handler(t, args));
	if (flag == 'x')
		return (x_handler(t, args));
	if (flag == 'X')
		return (x_upper_handler(t, args));
	if (flag == 'n')
		return (n_handler(t, args, len));
	if (flag == 'f')
		return (f_handler(t, args);
	return (-1);
}

int		flag_parser(char flag, t_params *t)
{
	int	result;

	result = 0;
	if (flag == '0' && (result = 1))
		t->flag = t->flag | PF_ZERO;
	if (flag == '-' && (result = 1))
		t->flag = t->flag | PF_MINUS;
	if (flag == '+' && (result = 1))
		t->flag = t->flag | PF_PLUS;
	if (flag == ' ' && (result = 1))
		t->flag = t->flag | PF_SPACE;
	if (flag == '#' && (result = 1))
		t->flag = t->flag | PF_GRILL;
	return (result);
}
