/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_makers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 09:34:24 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:50:02 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	sprite_array_maker(t_compose *t)
{
	t_spr_list	*spr;
	t_spr_list	*tmp;
	int			i;

	tmp = t->spr_struct;
	spr = t->spr_struct;
	while (tmp && (t->result->spr_len++) > -1)
		tmp = tmp->next;
	if (!(t->result->spr = malloc(sizeof(int) * t->result->spr_len)))
		map_error("MAP: sprite array maker error!", t, 0, -1);
	i = 0;
	while (spr)
	{
		t->result->spr[i] = spr->coords;
		i++;
		tmp = spr;
		spr = spr->next;
		free(tmp);
	}
}

void	map_array_maker(t_compose *t)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = t->map_struct;
	if (!(t->result->map = malloc(sizeof(char **) * (t->max_x + 1))))
		map_error("MAP: map maker error!", t, 0, -1);
	t->result->map[t->max_x] = 0;
	while (t->map_struct)
	{
		if (!(t->result->map[i] = malloc(sizeof(char *) * (t->max_y + 1))))
			map_malloc_error(i - 1, t);
		t->result->map[i][t->max_y] = 0;
		j = -1;
		while (t->map_struct->content[++j])
			t->result->map[i][j] = t->map_struct->content[j];
		while (j < t->max_y)
			t->result->map[i][j++] = ' ';
		i++;
		tmp = t->map_struct;
		t->map_struct = t->map_struct->next;
		free(tmp->content);
		free(tmp);
	}
}
