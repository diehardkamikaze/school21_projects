/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:40:32 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:56:25 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	handle_moving_ws(int dir, t_all *t)
{
	int		changed;
	double	tmp_y;
	double	tmp_x;

	tmp_y = t->plr->y + t->plr->dir_y * MOVE_SPEED * dir;
	tmp_x = t->plr->x + t->plr->dir_x * MOVE_SPEED * dir;
	changed = 0;
	if (t->map[(int)tmp_x][(int)t->plr->y] == 'L' && (changed = 1))
		t->plr->x = tmp_x;
	if (t->map[(int)t->plr->x][(int)tmp_y] == 'L' && (changed = 1))
		t->plr->y = tmp_y;
	if (changed)
		return (dir);
	return (0);
}

int	handle_moving_ad(double dir, t_all *t)
{
	int		changed;
	double	tmp_y;
	double	tmp_x;

	tmp_y = t->plr->y + (t->plr->dir_x * dir) * MOVE_SPEED;
	tmp_x = t->plr->x + (-t->plr->dir_y * dir) * MOVE_SPEED;
	changed = 0;
	if (t->map[(int)tmp_x][(int)t->plr->y] == 'L' && (changed = 1))
		t->plr->x = tmp_x;
	if (t->map[(int)t->plr->x][(int)tmp_y] == 'L' && (changed = 1))
		t->plr->y = tmp_y;
	if (changed)
		return (10 * (int)dir);
	return (0);
}

int	handle_rotating(int dir, t_all *t)
{
	double old_dir_x;
	double old_plane_x;
	double angle;

	old_dir_x = t->plr->dir_x;
	old_plane_x = t->plr->plane_x;
	angle = dir * ROT_SPEED;
	t->plr->dir_x = t->plr->dir_x * cos(angle) - t->plr->dir_y * sin(angle);
	t->plr->dir_y = old_dir_x * sin(angle) + t->plr->dir_y * cos(angle);
	t->plr->plane_x = t->plr->plane_x * cos(angle) - \
		t->plr->plane_y * sin(angle);
	t->plr->plane_y = old_plane_x * sin(angle) + t->plr->plane_y * cos(angle);
	return (dir * 5);
}

int	handle_vertical_rotation(int dir, t_all *t)
{
	double	tmp;

	tmp = t->plr->vertical + 0.1 * dir;
	if (tmp <= 0.8 && tmp >= -0.8)
	{
		t->plr->vertical = tmp;
		return (100 * dir);
	}
	return (0);
}
