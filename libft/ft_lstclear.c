/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:04:38 by mchau             #+#    #+#             */
/*   Updated: 2020/11/10 05:05:44 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = 0;
	tmp = *lst;
	if (tmp == 0)
		return ;
	while (tmp)
	{
		tmp = tmp->next;
		ft_lstdelone(*lst, &(*del));
		*lst = tmp;
	}
}
