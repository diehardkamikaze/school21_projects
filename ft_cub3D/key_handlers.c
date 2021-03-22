/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:44:35 by mchau             #+#    #+#             */
/*   Updated: 2021/03/22 14:41:55 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

int	test_handler(int keycode, void *param)
{
	t_all	*t = (t_all *)param;

	if (keycode == 53)
	{
		mlx_destroy_image(t->game->mlx, t->game->img);
		mlx_destroy_window(t->game->mlx, t->game->win);
		free (t->game->mlx);
		free_wrapper(t);
		exit(0);
	}
	if (keycode == 2)
	{
		float rotSpeed = -PI/2;
		t->plr->y += (t->plr->dirX * sin(rotSpeed) + t->plr->dirY * cos(rotSpeed)) * 0.1;
		t->plr->x += (t->plr->dirX * cos(rotSpeed) - t->plr->dirY * sin(rotSpeed)) * 0.1;
	}
	if (keycode == 0)
	{
		float rotSpeed = PI/2;
		t->plr->y += (t->plr->dirX * sin(rotSpeed) + t->plr->dirY * cos(rotSpeed)) * 0.1;
		t->plr->x += (t->plr->dirX * cos(rotSpeed) - t->plr->dirY * sin(rotSpeed)) * 0.1;
	}
	if (keycode == 13)
	{
		t->plr->y += t->plr->dirY * 0.1;
		t->plr->x += t->plr->dirX * 0.1;
	}
	if (keycode == 1)
	{
		t->plr->y -= t->plr->dirY * 0.1;
		t->plr->x -= t->plr->dirX * 0.1;
	}
	if (keycode == 123)
	{
	  float rotSpeed = 0.05;
	  float oldDirX = t->plr->dirX;
      t->plr->dirX = t->plr->dirX * cos(rotSpeed) - t->plr->dirY * sin(rotSpeed);
      t->plr->dirY = oldDirX * sin(rotSpeed) + t->plr->dirY * cos(rotSpeed);
      double oldPlaneX = t->plr->planeX;
      t->plr->planeX = t->plr->planeX * cos(rotSpeed) - t->plr->planeY * sin(rotSpeed);
      t->plr->planeY = oldPlaneX * sin(rotSpeed) + t->plr->planeY * cos(rotSpeed);
	}
	if (keycode == 124)
	{
	  float rotSpeed = -0.05;
	  float oldDirX = t->plr->dirX;
      t->plr->dirX = t->plr->dirX * cos(rotSpeed) - t->plr->dirY * sin(rotSpeed);
      t->plr->dirY = oldDirX * sin(rotSpeed) + t->plr->dirY * cos(rotSpeed);
      double oldPlaneX = t->plr->planeX;
      t->plr->planeX = t->plr->planeX * cos(rotSpeed) - t->plr->planeY * sin(rotSpeed);
      t->plr->planeY = oldPlaneX * sin(rotSpeed) + t->plr->planeY * cos(rotSpeed);
	}
	mlx_destroy_image(t->game->mlx, t->game->img);
	fill_image_by_map(t);//получается перерисовываешь при нажатии любой клавиши - чего делать ненужно
	// -> == 124, -< == 123, W== 13 , A == 0, S == 1, D == 2
	return (1);
}

int	x_handler(void *param)
{
	t_all   *t = (t_all *)param;
	mlx_destroy_window(t->game->mlx, t->game->win);
	free (t->game->mlx);
	free_wrapper(t);
	exit(0);
	return (1);
}

int	the_handler(void *param)
{
	t_all   *t = (t_all *)param;
	if (t->map)
		printf("test");
	return printf("test");
}
