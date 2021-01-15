/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:36:04 by mchau             #+#    #+#             */
/*   Updated: 2020/11/11 22:55:45 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_new;
	unsigned char	*src_new;
	unsigned char	stop;

	stop = (unsigned char)c;
	dst_new = (unsigned char *)dst;
	src_new = (unsigned char *)src;
	while (n--)
	{
		*dst_new = *src_new;
		if (*src_new == stop)
			return (dst_new + 1);
		src_new++;
		dst_new++;
	}
	return (0);
}
