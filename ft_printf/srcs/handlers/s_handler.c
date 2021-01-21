/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:27:01 by mchau             #+#    #+#             */
/*   Updated: 2021/01/21 14:49:32 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		s_handler_char(t_params *t, char *s)
{
	int		result_count;
	int		n;

	result_count = 0;
	if (s == 0 && (result_count = 6))
		s = "(null)";
	else
		while (s[result_count] != 0)
			result_count++;
	if (t->precision >= 0 && result_count > t->precision)
		result_count = t->precision;
	n = t->width > result_count ? t->width - result_count : 0;
	if (!(t->flags | PF_MINUS))
		print_nchr(' ', n);
	write(1, s, result_count);
	if (t->flags | PF_MINUS)
		print_nchr(' ', n);
	return (result_count + n);
}

int		get_len_using_prec(int *s, int precision)
{
	int len;
	int	current;

	len = 0;
	while (*s != 0)
	{
		current = 1;
		if (*s > 127)
			current += 1;
		if (*s > 2047)
			current += 1;
		if (*s > 65535)
			current += 1;
		if (precision >= 0 && current + len > precision)
			return (len);
		len += current;
		s++;
	}
	return (len);
}

int		s_handler_wchar(t_params *t, int *s)
{
	int				result_count;
	int				i;
	unsigned int	character;

	i = 0;
	result_count = get_len_using_prec(s, t->precision);
	t->width = t->width > result_count ? t->width - result_count : 0;
	if (!(t->flags | PF_MINUS))
		print_nchr(' ', t->width);
	while (i < result_count)
	{
		i += write(1, &character, convert_to_utf8(*s, &character));
		s++;
	}
	if (t->flags | PF_MINUS)
		print_nchr(' ', t->width);
	return (result_count + t->width);
}

int		s_handler(t_params *t, va_list arg)
{
	void *s;

	s = va_arg(arg, void *);
	if (s == 0 || t->length != 'l')
		return (s_handler_char(t, s));
	else
		return (s_handler_wchar(t, s));
}
