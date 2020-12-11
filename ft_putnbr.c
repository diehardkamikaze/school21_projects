/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:46:37 by mchau             #+#    #+#             */
/*   Updated: 2020/12/02 18:07:12 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_itoa(size_t  input, char *buffer, int radix)
{
	char	sign;

	sign = 0;
	if (input < 0 && (sign = -1))
		input *= -1;
	*buffer = '0';
	while (input != 0)
    {
        int remainder = input % radix;
        *buffer = (remainder >= 10) ? (remainder - 10) + 'a' : remainder + '0';
        input = input/radix;
		buffer--;
    }
	if (sign)
		*buffer = '-';
}
