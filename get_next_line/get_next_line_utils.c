/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 08:51:25 by mchau             #+#    #+#             */
/*   Updated: 2020/11/18 18:09:45 by mchau            ###   ########.fr       */
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	char		*tmp;

	if (!s)
		return (0);
	result = 0;
	result = (char *)malloc(len + 1);
	if (!result)
		return (result);
	result[len] = 0;
	tmp = result;
	while (len-- && *s != 0)
		*tmp++ = *s++;
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
	return (-1);
}

t_list	*ft_lstnew(char *content, int len)
{
	t_list	*tmp;

	tmp = 0;
	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = 0;
		tmp->len = len;
	}
	return (tmp);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
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
}
