/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:39:15 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 17:10:18 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_preprocessor(t_params *t)
{
	if (t->width < 0)
	{
		t->width = -1 * t->width;
		t->flags = t->flags | PF_MINUS;
	}
	if (t->flags & PF_MINUS)
		t->flags = t->flags & 254;
	return (1);
}

int	flag_parser(char c, t_params *t)
{
	int	result;

	result = 0;
	if (c == '0' && (result = 1))
		t->flags = t->flags | PF_ZERO;
	if (c == '-' && (result = 1))
		t->flags = t->flags | PF_MINUS;
	if (c == '+' && (result = 1))
		t->flags = t->flags | PF_PLUS;
	if (c == ' ' && (result = 1))
		t->flags = t->flags | PF_SPACE;
	if (c == '#' && (result = 1))
		t->flags = t->flags | PF_GRILL;
	return (result);
}

int	length_parser(char *str, t_params *t)
{
	if (*str == 'l' && str++)
	{
		t->length = 'l';
		if (*str == 'l' && (t->length = 'l' + 'l'))
			return (2);
		return (1);
	}
	if (*str == 'h' && str++)
	{
		t->length = 'h';
		if (*str == 'h' && (t->length = 'h' + 'h'))
			return (2);
		return (1);
	}
	return (0);
}

int	ft_router(char flag, t_params *t, va_list args)
{
	if (flag == 's')
		return (t->printed += s_handler(t, args));
	if (flag == 'c')
		return (t->printed += c_handler(t, args));
	if (flag == '%')
		return (t->printed += percent_handler(t, args));
	if (flag == 'd' || flag == 'i')
		return (t->printed += d_i_handler(t, args));
	if (flag == 'p')
		return (t->printed += p_handler(t, args));
	if (flag == 'u')
		return (t->printed += u_handler(t, args));
	if (flag == 'x')
		return (t->printed += x_handler(t, args));
	if (flag == 'X')
		return (t->printed += x_upper_handler(t, args));
	if (flag == 'n')
		return (t->printed += n_handler(t, args));
	return (-1);
}

int	ft_parser(char *str, t_params *t, va_list args)
{
	char	*start;

	start = str;
	while (flag_parser(*str, t))
		str++;
	if (*str == '*' && str++)
		t->width = va_arg(args, int);
	else
		t->width = ft_strtol(str, &str, 10);
	if (*str == '.' && str++)
	{
		if (*str == '*' && str++)
			t->precision = va_arg(args, int);
		else
			t->precision = ft_strtol(str, &str, 10);
	}
	str += length_parser(str, t);
	if (ft_preprocessor(t) && ft_router(*str, t, args) == -1)
		return (-1);
	return (str + 1 - start);
}
