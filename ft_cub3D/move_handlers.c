/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:40:32 by mchau             #+#    #+#             */
/*   Updated: 2021/03/23 11:20:27 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

int	handle_moving_ws(int dir, t_all *t)
{
		t->plr->y += t->plr->dirY * MOVE_SPEED * dir;
		t->plr->x += t->plr->dirX * MOVE_SPEED * dir;
		fill_image_by_map(t);
		return (1);
}

int	handle_moving_ad(float dir, t_all *t)
{
		t->plr->y += (t->plr->dirX * sin(dir) + t->plr->dirY * cos(dir)) * MOVE_SPEED;
		t->plr->x += (t->plr->dirX * cos(dir) - t->plr->dirY * sin(dir)) * MOVE_SPEED;
		fill_image_by_map(t);
		return (1);
}

int handle_rotating(int dir, t_all *t)
{
	float old_dir_x;
	float old_plane_x;
	float angle;

	old_dir_x = t->plr->dirX;
	old_plane_x = t->plr->planeX;
	angle = dir * ROT_SPEED;
	t->plr->dirX = t->plr->dirX * cos(angle) - t->plr->dirY * sin(angle);
	t->plr->dirY = old_dir_x * sin(angle) + t->plr->dirY * cos(angle);
	t->plr->planeX = t->plr->planeX * cos(angle) - t->plr->planeY * sin(angle);
    t->plr->planeY = old_plane_x * sin(angle) + t->plr->planeY * cos(angle);
	fill_image_by_map(t);
	return (1);
}
