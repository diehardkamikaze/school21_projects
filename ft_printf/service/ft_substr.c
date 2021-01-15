/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 04:12:48 by mchau             #+#    #+#             */
/*   Updated: 2020/11/12 21:20:41 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *result;

	if (!s)
		return (0);
	result = 0;
	if (ft_strlen(s) <= start)
	{
		result = (char *)malloc(1);
		if (result)
			result[0] = 0;
		return (result);
	}
	result = (char *)malloc(len + 1);
	if (!result)
		return (result);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
