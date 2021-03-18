/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 03:06:27 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 03:26:56 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t n;

	if (!src || !dst)
		return (0);
	n = 0;
	while (n < dstsize)
	{
		dst[n] = src[n];
		if (src[n] == 0)
			break ;
		n++;
	}
	if (n == dstsize && dstsize != 0)
		dst[n - 1] = 0;
	while (src[n])
		n++;
	return (n);
}
