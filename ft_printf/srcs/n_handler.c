/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:02:07 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 12:07:49 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	n_handler(t_params *t, va_list args)
{
	void	*n;

	n = va_arg(args, void *);
	if (t->length == 'h')
		*((short int *)n) = t->printed;
	if (t->length == 'h' + 'h')
		*((char *)n) = t->printed;
	if (t->length == 'l')
		*((long int *)n) = t->printed;
	if (t->length == 'l' + 'l')
		*((long long int *)n) = t->printed;
	return (0);
}
