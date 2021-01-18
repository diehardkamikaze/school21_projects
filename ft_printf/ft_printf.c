/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:01:35 by mchau             #+#    #+#             */
/*   Updated: 2021/01/17 16:42:56 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parser(char *str, t_params *t, va_list args)
{
	char *start;

	start = str;
	while (ft_strchr("-0", *str) != 0)
		str += flag_handler(*str, t);
	if (*str == '*' && str++)
		t->width = va_arg(args, int);
	else
		t->width = ft_strtol(str, &str, 10);
	if (*str == '.' && str++ && (t->dot = 1))
	{
		if(*str == '*' && str++)
			t->precision = va_arg(args, int);
		else
			t->precision = ft_strtol(str, &str, 10);
	};
	if (ft_strchr("cspdiuxX%", *str) && spec_handler(*str, t))
		return (str + 1 - start);
	return (-1);
}

int	clear_spec(t_params *t)
{
	t->width = 0;
	t->precision = 0;
	t->dot = 0;
	t->specific = 0;
	t->zero = 0;
	t->minus = 0;
	return (1);
}

int		ft_vprintf(char *format, va_list args)
{
	t_params	*parse_result;
	int			printed_count;
	int			parsing_shift;

	if(!(parse_result = malloc(sizeof(t_params))))
		return (-1);
	printed_count = 0;
	parsing_shift = 0;
	while (*format)
	{
		if (*format == '%' && clear_spec(parse_result))
		{
			if ((parsing_shift = ft_parser(format + 1, parse_result, args)) == -1)
				return (-1);
			printed_count += parse_result->specific(parse_result, args);
		/*	printf("width: %d\n", parse_result->width);
			printf("precision: %d\n", parse_result->precision);
			printf("flag 0: %d\n", (int)parse_result->zero);
			printf("flag minus: %d\n", (int)parse_result->minus);
			printf("------\n") ;*/
			format += parsing_shift;
		}
		else
			printed_count += write(1, format, 1);
		format++;
	}
	free(parse_result);
	return (printed_count);
}

int	ft_printf(const char *s, ...)
{
	int result;

	result = 0;
	va_list args;
	va_start(args, s);
	result = ft_vprintf((char *)s, args);
	va_end(args);
	return (result);
}

