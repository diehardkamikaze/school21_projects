/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:08:53 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 05:11:29 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*start;

	tmp = 0;
	prev = 0;
	start = 0;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (tmp == 0)
		{
			ft_lstclear(&start, &(*del));
			return (0);
		}
		if (prev)
			prev->next = tmp;
		else
			start = tmp;
		prev = tmp;
		lst = lst->next;
	}
	return (start);
}
