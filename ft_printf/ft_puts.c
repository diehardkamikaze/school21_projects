/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:55:56 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 18:45:33 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		error_log(t_params *t, va_list arg)
{
	if (t && arg)
		return (-1);
	return (-1);
}

void	ft_putstr(char *s)
{
	while (*s != 0)
	{
		write(1, s, 1);
		s++;
	}
}

void	print_nchr(char c, int n)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}
