/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:17:11 by mchau             #+#    #+#             */
/*   Updated: 2021/01/15 15:23:55 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	error_log(char *flag, char *message)
{
	ft_putstr("error: flag '");
	ft_putstr(flag);
	write(1, "' \n", 3);
	ft_putstr( message);
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
