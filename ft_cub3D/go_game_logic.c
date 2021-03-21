/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:03:28 by mchau             #+#    #+#             */
/*   Updated: 2021/03/21 12:01:37 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void    scale_pixel(t_all *t, int x, int y, int color);

void	fill_image_by_map(t_all *t)
{
	if(!(t->game->img = mlx_new_image(t->game->mlx, t->maze->w_h / 1000000, t->maze->w_h % 1000000)))
		exit_with_message("GAME: mlx_image_init malloc error", t);

	int bpp;
	int size_line;
	int endian;

	t->game->addr = (unsigned int *)(mlx_get_data_addr(t->game->img, &bpp, &size_line, &endian)); // polu4aem buffer
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
	mlx_put_image_to_window(t->game->mlx, t->game->win, t->game->img, 0, 0);
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
			t->game->addr[(x + i) * t->maze->w_h / 1000000 + (y + j)] = color;
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
	fill_image_by_map(t);
	mlx_hook(game.win, 17, 0, x_handler, t); // [x] push
	mlx_hook(game.win, 2, (1L << 0), test_handler, t);
	mlx_loop(game.mlx);
}
