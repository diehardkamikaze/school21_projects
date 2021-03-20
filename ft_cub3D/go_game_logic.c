/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:03:28 by mchau             #+#    #+#             */
/*   Updated: 2021/03/20 12:43:13 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void    scale_pixel(t_all *t, int x, int y, int color);

void	show_map(t_all *t)
{
	int i = 0;
	int j;

	while (t->map[i])
	{
		j = 0;
		while (t->map[i][j])
		{
			if ((int)t->plr->x == i && (int)t->plr->y == j)
				scale_pixel(t, i, j, 0xcd6889);
			else if (t->map[i][j] == '1')
				scale_pixel(t, i, j, 0xffc0cb);
			j++;
		}
		i++;
	}
}

void	scale_pixel(t_all *t, int x, int y, int color)
{
	int i;
	int j;
	int size;

	size = 20;
	x = size * x;
	y = size * y;
	i = -1;
	j = -1;
	while (++i < size && (j = -1))
		while (++j < size)
			mlx_pixel_put(t->game->mlx, t->game->win, y + j, x + i, color);
}
void	go_game_logic(t_all *t)
{
	t_win game;

	t->game = &game;
	if (!(game.mlx = mlx_init()))
		exit_with_message("GAME: mlx_init malloc error", t);
	//preprocess window reso situation
	if (!(game.win = mlx_new_window(game.mlx, (int)(t->maze->w_h / 1000000),\
					(int)(t->maze->w_h % 1000000), "mchau")))
		exit_with_message("GAME: mlx_new_window malloc error", t);
	show_map(t);
//	mlx_key_hook (game.win, test_handler, t);
	mlx_hook(game.win, 17, 0, x_handler, t); // [x] push
	mlx_hook(game.win, 2, (1L << 0), test_handler, t);
	//mlx_loop_hook(game.win, the_handler, t); //loop пока не шагает?
	mlx_loop(game.mlx);
}
