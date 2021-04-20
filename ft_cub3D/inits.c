/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:12:46 by mchau             #+#    #+#             */
/*   Updated: 2021/04/20 15:27:04 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cub3D.h>

t_all	*initialize_master_struct(int fd)
{
	t_all *t;

	if (!(t = malloc(sizeof(t_all))))
		exit_with_message("t_all init: malloc error!", 0);
	t->map = 0;
	t->maze = 0;
	t->plr = 0;
	t->spr = 0;
	t->spr_len = 0;
	if (!(t->maze = malloc(sizeof(t_maze_params))))
		maze_error("t_all init maze: malloc error!", t, 0, fd);
	t->maze->w_h = 0;
	t->maze->c_f[0] = 16777216;
	t->maze->c_f[1] = 16777216;
	ft_bzero(t->maze->textures, 5 * sizeof(char *));
	ft_bzero(t->txt_img, 5 * sizeof(void *));
	if (!(t->plr = malloc(sizeof(t_plr))))
		maze_error("t_all init plr: malloc error!", t, 0, fd);
	t->plr->x = -1;
	t->plr->y = -1;
	t->plr->vertical = 0;
	t->pressed.key_w = 0;
	t->pressed.key_a = 0;
	t->pressed.key_s = 0;
	t->pressed.key_d = 0;
	t->pressed.key_arrow_bottom = 0;
	t->pressed.key_arrow_top = 0;
	t->pressed.key_arrow_left = 0;
	t->pressed.key_arrow_right = 0;
	return (t);
}

void	init_map_vars(t_compose *t, t_all *result)
{
	t->result = result;
	t->map_struct = 0;
	t->spr_struct = 0;
	t->max_x = 0;
	t->max_y = 0;
}

void init_txt_array(t_all *t)
{
	int i;
	int width;
	int height;

	i = 0;
	while (i < 5)
	{
		t->txt_img[i] = mlx_xpm_file_to_image(t->game.mlx, \
				t->maze->textures[i], &width, &height);
		if (t->txt_img[i] == 0)
			exit_with_message("Invalid texture", t);
		i++;
	}
}

void	init_game (t_all *t)
{
	int bpp;
	int size_line;
	int endian;

	if (!(t->game.mlx = mlx_init()))
		exit_with_message("GAME: mlx_init malloc error", t);
	if(!(t->game.img = mlx_new_image(t->game.mlx, t->maze->w_h / 1000000, t->maze->w_h % 1000000)))
		exit_with_message("GAME: mlx_image_init malloc error", t);
	t->game.addr = (unsigned int *)(mlx_get_data_addr(t->game.img, &bpp, &size_line, &endian));
	t->game.win = 0;
	init_txt_array(t);
	fill_image_by_map(t);
}
