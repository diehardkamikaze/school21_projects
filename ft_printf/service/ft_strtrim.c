/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:14:32 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 08:40:51 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_left_right_offset(char const *s1, char const *set, int *left,\
		int *right)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1[*left])
			*left = *left + 1;
		if (set[i] == s1[*right])
			*right = *right - 1;
		i++;
	}
}

char	*return_empty_string(void)
{
	char *result;

	result = 0;
	result = (char *)malloc(1);
	if (result)
		result[0] = '\0';
	return (result);
}

void	rightchecker(int *right_checker, int right, int len)
{
	if (*right_checker == len || *right_checker == right)
		*right_checker = len;
	else
		*right_checker = right;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	left;
	int	right;
	int	left_checker;
	int right_checker;
	int len;

	if (!s1)
		return (0);
	left = 0;
	left_checker = left;
	len = ft_strlen(s1);
	right = len - 1;
	right_checker = right;
	while (left <= right && (left_checker != -1 || right_checker != len))
	{
		set_left_right_offset(s1, set, &left, &right);
		if (left_checker == -1 || left_checker == left)
			left_checker = -1;
		else
			left_checker = left;
		rightchecker(&right_checker, right, len);
	}
	if (left > right)
		return (return_empty_string());
	return (ft_substr(s1, left, right - left + 1));
}
