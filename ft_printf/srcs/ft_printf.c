/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:01:35 by mchau             #+#    #+#             */
/*   Updated: 2021/02/24 10:12:29 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		clear_spec(t_params *t)
{
	t->width = 0;
	t->precision = -1;
	t->flags = 0;
	t->length = 0;
	t->fp = 0;
	return (1);
}

int		ft_vprintf(char *format, va_list args)
{
	t_params	parse_result;
	int			parsing_shift;

	parse_result.printed = 0;
	parsing_shift = 0;
	while (*format)
	{
		if (*format == '%' && clear_spec(&parse_result))
		{
			if ((parsing_shift =\
						ft_parser(format + 1, &parse_result, args)) == -1)
				return (-1);
			format += parsing_shift;
		}
		else
			parse_result.printed += write(1, format, 1);
		format++;
	}
	return (parse_result.printed);
}

int		ft_printf(const char *s, ...)
{
	int		result;
	va_list	args;

	result = 0;
	va_start(args, s);
	result = ft_vprintf((char *)s, args);
	va_end(args);
	return (result);
}
