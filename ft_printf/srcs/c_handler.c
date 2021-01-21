/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:14:59 by mchau             #+#    #+#             */
/*   Updated: 2021/01/21 15:08:17 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		c_handler(t_params *t, va_list arg)
{
	unsigned int	character;
	unsigned int	temp;
	int				result_count;

	result_count = 1;
	if (t->length == 'l')
	{
		temp = va_arg(arg, unsigned int);
		result_count = convert_to_utf8(temp, &character);
	}
	else
		character = (char)va_arg(arg, int);
	t->width = t->width > result_count ? t->width - result_count : 0;
	if (!(t->flags & PF_MINUS))
		print_nchr(' ', t->width);
	write(1, &character, result_count);
	if (t->flags & PF_MINUS)
		print_nchr(' ', t->width);
	return (result_count + t->width);
}
