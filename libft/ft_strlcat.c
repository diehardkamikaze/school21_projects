/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 03:33:02 by mchau             #+#    #+#             */
/*   Updated: 2020/11/11 23:31:53 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dstlen;
	size_t		toappend;
	const char	*orig_src;

	orig_src = src;
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
		return (dstsize + ft_strlen(src));
	toappend = dstsize - dstlen - 1;
	dst = dst + dstlen;
	while (toappend--)
	{
		*dst = *src;
		if (*src == 0)
			break ;
		dst++;
		src++;
	}
	*dst = 0;
	return (dstlen + ft_strlen(orig_src));
}
