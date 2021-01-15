/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:09 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 02:50:00 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_reversed_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *dst_new;
	unsigned char *src_new;

	dst_new = (unsigned char *)dst;
	src_new = (unsigned char *)src;
	while (n--)
		dst_new[n] = src_new[n];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (src < dst && src + len > dst)
		return (ft_reversed_memcpy(dst, src, len));
	else
		return (ft_memcpy(dst, src, len));
}
