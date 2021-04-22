/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:06:28 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:58:32 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	result[len] = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	return (result);
}
