/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 04:43:15 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 04:52:25 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*result;
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	result = 0;
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	result[len] = 0;
	while (i < len)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	return (result);
}
