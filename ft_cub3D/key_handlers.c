/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:44:35 by mchau             #+#    #+#             */
/*   Updated: 2021/03/21 18:06:44 by mchau            ###   ########.fr       */
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
		t->plr->y += 0.1;
	if (keycode == 0)
		t->plr->y -= 0.1;
	if (keycode == 13)
		t->plr->x -= 0.1;
	if (keycode == 1)
		t->plr->x += 0.1;
	if (keycode == 124)
		t->plr->dir -= 0.1;
	if (keycode == 123)
		t->plr->dir += 0.1;
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
