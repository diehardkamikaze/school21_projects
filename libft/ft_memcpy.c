/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:25:02 by mchau             #+#    #+#             */
/*   Updated: 2020/11/09 22:35:54 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_new;
	unsigned char	*src_new;

	if (!dst && !src)
		return (0);
	dst_new = (unsigned char *)dst;
	src_new = (unsigned char *)src;
	while (n--)
	{
		*dst_new = *src_new;
		dst_new++;
		src_new++;
	}
	return (dst);
}
