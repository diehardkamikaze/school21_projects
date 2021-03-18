/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:13:15 by mchau             #+#    #+#             */
/*   Updated: 2020/11/11 23:13:02 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**make_array(char const *s, char c)
{
	int		len;
	int		i;
	char	**result_array;

	i = 0;
	len = 0;
	result_array = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
		{
			len++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
	}
	result_array = (char **)malloc(sizeof(char *) * (len + 1));
	if (result_array)
		result_array[len] = 0;
	return (result_array);
}

int		free_if_needed(char **arr, int pos)
{
	int i;

	i = 0;
	if (!arr[pos])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		from;
	int		i;
	int		word;

	if (!s)
		return (0);
	i = 0;
	word = 0;
	result = make_array(s, c);
	if (!result)
		return (0);
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		from = i;
		while (s[i] != c && s[i] != 0)
			i++;
		if (from < i)
			result[word] = ft_substr(s, from, i - from);
		if (from < i && free_if_needed(result, word++))
			return (0);
	}
	return (result);
}
