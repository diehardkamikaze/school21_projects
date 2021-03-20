/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:19:04 by mchau             #+#    #+#             */
/*   Updated: 2021/03/20 09:58:32 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	flood_fill(t_compose *t, int pos_x, int pos_y)
{
	if (0 > pos_x || pos_x > (t->max_x - 1) || pos_y > (t->max_y - 1) \
			|| 0 > pos_y || t->result->map[pos_x][pos_y] == ' ')
		exit_with_message("FF: hole in wall!", t->result);
	if (t->result->map[pos_x][pos_y] != '1' && \
			t->result->map[pos_x][pos_y] != 'S')
		t->result->map[pos_x][pos_y] = 'S';
	else
		return ;
	flood_fill(t, pos_x + 1, pos_y);
	flood_fill(t, pos_x - 1, pos_y);
	flood_fill(t, pos_x, pos_y + 1);
	flood_fill(t, pos_x, pos_y - 1);
}
