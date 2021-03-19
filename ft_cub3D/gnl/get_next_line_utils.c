/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 08:51:25 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 11:22:50 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*result;
	char	*tmp;

	if (!s)
		return (0);
	result = 0;
	s = s + start;
	result = (char *)malloc(len + 1);
	if (!result)
		return (result);
	result[len] = 0;
	tmp = result;
	while (len--)
	{
		*tmp = *s;
		s++;
		tmp++;
	}
	return (result);
}

int		ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	tmp = 0;
	tmp = *lst;
	if (tmp == 0)
		return (-1);
	while (tmp)
	{
		tmp = tmp->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (0);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*tmp;

	tmp = 0;
	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = 0;
	}
	return (tmp);
}

int		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}
