/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:03:28 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:54:03 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	init_raycasting_vars(t_draw *d)
{
	d->camera_x = 2 * d->x / (double)d->width - 1;
	d->raydir_x = d->dir_x + d->camera_x * d->plane_x;
	d->raydir_y = d->dir_y + d->camera_x * d->plane_y;
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	d->delta_dist_x = fabs(1 / d->raydir_x);
	d->delta_dist_y = fabs(1 / d->raydir_y);
	if (d->raydir_x < 0 && (d->step_x = -1))
		d->side_dist_x = (d->pos_x - d->map_x) * d->delta_dist_x;
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->pos_x) * d->delta_dist_x;
	}
	if (d->raydir_y < 0 && (d->step_y = -1))
		d->side_dist_y = (d->pos_y - d->map_y) * d->delta_dist_y;
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - d->pos_y) * d->delta_dist_y;
	}
}

void	ray_casting_cycle(t_all *t, t_draw *d)
{
	while (1)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (t->map[d->map_x][d->map_y] == '1')
			return ;
	}
}

void	wall_dist_to_wall_height(t_draw *d)
{
	if (d->side == 0)
		d->wall_dist = (d->map_x - d->pos_x +\
				(1 - d->step_x) / 2) / d->raydir_x;
	else
		d->wall_dist = (d->map_y - d->pos_y +\
				(1 - d->step_y) / 2) / d->raydir_y;
	d->line_height = (int)(d->width * 0.75 / d->wall_dist);
	d->draw_start = -d->line_height / 2 + d->height / 2 + d->vert_pos;
	if (d->draw_start < 0)
		d->draw_start = 0;
	if (d->draw_start > d->height)
		d->draw_start = d->height - 1;
	d->draw_end = d->line_height / 2 + d->height / 2 + d->vert_pos;
	if (d->draw_end >= d->height)
		d->draw_end = d->height - 1;
}

int		fill_image_by_game(t_all *t)
{
	t_draw	d;
	double	z_buffer[t->maze->w_h[0]];

	init_draw_vars(&d, t);
	while (d.x < d.width)
	{
		init_raycasting_vars(&d);
		ray_casting_cycle(t, &d);
		wall_dist_to_wall_height(&d);
		draw_ceil(&d, t);
		draw_texture(&d, t);
		draw_floor(&d, t);
		z_buffer[d.x] = d.wall_dist;
		d.x++;
	}
	draw_objects(t, &d, z_buffer);
	return (1);
}

void	go_game_logic(t_all *t)
{
	if (!(t->game.win = mlx_new_window(t->game.mlx, (int)(t->maze->w_h[0]),\
					(int)(t->maze->w_h[1]), "mchau")))
		exit_with_message("GAME: mlx_new_window malloc error", t);
	mlx_do_key_autorepeatoff(t->game.mlx);
	mlx_mouse_show();
	mlx_put_image_to_window(t->game.mlx, t->game.win, t->game.img, 0, 0);
	mlx_hook(t->game.win, 17, 0, exit_handler, t);
	mlx_hook(t->game.win, 2, 0, key_handler, t);
	mlx_hook(t->game.win, 3, 0, key_handler, t);
	mlx_loop_hook(t->game.mlx, key_state_checker, t);
	mlx_loop(t->game.mlx);
}
