/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:04:15 by mchau             #+#    #+#             */
/*   Updated: 2021/01/15 14:06:08 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//rename that and change header!
char	*ft_strchr(const char *s, int c)
{
	char *arr;

	arr = (char *)s;
	while (*arr != 0)
	{
		if (*arr == c)
			return (arr);
		arr++;
	}
	if (c == 0)
		return (arr);
	return (0);
}
