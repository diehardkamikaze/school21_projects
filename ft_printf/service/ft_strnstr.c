/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 23:41:58 by mchau             #+#    #+#             */
/*   Updated: 2020/11/12 05:31:38 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_hash(const char *needle, int to, int q, int base)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (i < to)
	{
		result = (result * base + needle[i]) % q;
		i++;
	}
	return (result);
}

int		get_offset(int base, int q, int nee_len)
{
	int result;

	result = 1;
	while (nee_len--)
		result = (result * base) % q;
	return (result);
}

char	*rabin_karp_matching(const char *hay, const char *nee, size_t nee_len,\
		size_t i)
{
	int	base;
	int	q;
	int	nee_hash;
	int	hay_hash;
	int	to_offset;

	q = 1471;
	base = 256;
	to_offset = get_offset(base, q, nee_len - 1);
	nee_hash = get_hash(nee, nee_len, q, base);
	hay_hash = get_hash(hay, nee_len, q, base);
	while (i--)
	{
		if (nee_hash == hay_hash)
			while (!ft_strncmp((const char *)hay, (const char *)nee, nee_len))
				return ((char *)hay);
		if (hay[nee_len] == 0)
			return (0);
		hay_hash = (((hay_hash + q - (to_offset * hay[0]) % q) % q) * 256 + \
				hay[nee_len]) % q;
		hay++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nee_len;
	size_t	hay_len;

	nee_len = ft_strlen(needle);
	if (!nee_len)
		return ((char *)haystack);
	hay_len = ft_strlen(haystack);
	if (hay_len < nee_len || len < nee_len)
		return (0);
	return (rabin_karp_matching(haystack, needle, nee_len, len - nee_len + 1));
}
