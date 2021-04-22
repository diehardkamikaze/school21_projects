/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:19:04 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:52:29 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	sprite_handler(int coords, t_compose *t)
{
	t_spr_list *tmp;

	if (!(tmp = malloc(sizeof(t_spr_list))))
		map_error("MAP: Error on spr malloc", t, 0, -1);
	tmp->coords = coords;
	tmp->next = t->spr_struct;
	t->spr_struct = tmp;
}

void	flood_fill(t_compose *t, int pos_x, int pos_y)
{
	if (0 > pos_x || pos_x >= t->max_x || pos_y >= t->max_y \
			|| 0 > pos_y || t->result->map[pos_x][pos_y] == ' ')
		exit_with_message("FF: hole in wall!", t->result);
	if (t->result->map[pos_x][pos_y] == '2')
		sprite_handler(pos_x * 1000 + pos_y, t);
	if (t->result->map[pos_x][pos_y] != '1' && \
			t->result->map[pos_x][pos_y] != 'L')
		t->result->map[pos_x][pos_y] = 'L';
	else
		return ;
	flood_fill(t, pos_x + 1, pos_y);
	flood_fill(t, pos_x - 1, pos_y);
	flood_fill(t, pos_x, pos_y + 1);
	flood_fill(t, pos_x, pos_y - 1);
}
