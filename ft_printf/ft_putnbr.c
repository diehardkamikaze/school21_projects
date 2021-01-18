/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:39:12 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 10:25:58 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_number_len(unsigned long input, int radix)
{
	if (input != 0)
		return (1 + ft_number_len(input / radix, radix));
	return (0);
}

void	ft_putnbr_positive(unsigned long input, int radix, char start)
{
	int remainder;
	char digit;

	remainder = input % radix;
	digit = (remainder >= 10) ? (remainder - 10) + start : remainder + '0';
	if (input / radix > 0)
	{
		ft_putnbr_positive(input / radix, radix, start);
		write(1, &digit, 1);
	}
	else
		write(1, &digit, 1);
}
