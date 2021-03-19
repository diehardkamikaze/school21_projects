/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_makers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:17:51 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 16:35:21 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	sprite_array_maker(t_compose *t)
{
	t_spr_list	*spr;
	t_spr_list	*tmp;
	int i;

	tmp = t->spr_struct;
	spr = t->spr_struct;
	while (tmp && (t->result->spr_len++) > -1)
		tmp = tmp->next;
	if (!(t->result->spr = malloc(sizeof(int) * t->result->spr_len)))
		map_error("MAP: sprite array maker error!", t, 0);
	i = 0;
	while (spr)
	{
		t->result->spr[i] = spr->coords;
		i++;
		tmp = spr;
		spr = spr->next;
		free(tmp);
	}
	printf("%d", t->result->spr[0]);
}
/*
void	map_maker(t_compose *t)
{
	t_list *tmp;
	t_list *chain;
	int i;
	int j;

	i = 0;
	tmp = t->map_struct;
	chain = t->map_struct;
	if (!(t->result->map = malloc(sizeof(char **) * t->max_x + 1)))
		map_error("MAP: map maker error!", &t, 0);
	t->result->map[t->max_x] = 0;
	while (chain)
	{
		if (!(t->result->map[i] = malloc(sizeof(char *) * t->max_y + 1)))
		{
			i--;
			while (i-- >= 0)
				free(t->result->map[i]);
			free(t->result->map);
			t->result->map = 0;
			map_error("MAP: map maker error 2!", &t, 0);
		}
		t->result->map[i][t->max_y] = 0;
		j = 0;
		while (chain->content[j])
			t->result->map[i][j] = chain->content[j++];
		while (j < t->max_y)
			t->result->map[i][j++] = ' ';
		i++;
		tmp = chain;
		chain = chain->next;
		free(tmp->content);
		free(tmp);
	}
} */
