/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:16:15 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 05:45:58 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		arr_len(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	while (n / 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*get_array(int size)
{
	char	*result;

	result = 0;
	result = (char *)malloc(size + 1);
	if (result)
	{
		result[size - 1] = '0';
		result[size] = 0;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		sign;

	sign = 1;
	i = arr_len(n);
	result = get_array(i);
	if (!result)
		return (0);
	if (n < 0)
	{
		result[0] = '-';
		sign = -1;
	}
	i--;
	while (n)
	{
		result[i] = (n % 10) * sign + '0';
		n = n / 10;
		i--;
	}
	return (result);
}
