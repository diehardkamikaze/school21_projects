/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:01:35 by mchau             #+#    #+#             */
/*   Updated: 2020/12/11 17:05:33 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_printf(const char *s, ...)
{
	va_list ap;
	char	*permitted_flags;
	int	counter;

	char *k;

	permitted_flags = "cspdiuxX%-0.*nfge";
	counter = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if(*s == 'c')
			{
				char l = va_arg(ap, int);
				write(1, &l, 1);
			}
			if(*s == 's')
			{
				k = va_arg(ap, char *);
				if (!k)
					write(1, "(null)", 6);
				else
					while (*k)
					 	write(1, k++, 1);
			}
			if(*s == 'n')
			{
				// void *k = &(va_arg(ap, int *));
				func_n(va_arg(ap, int *), counter);

			}
			s++;
		}
		else
		{
			write(1, s, 1);
			s++;
			counter++;
		}
	}
	va_end(ap);
	return (counter);
}
