/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:10:25 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 18:39:17 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cub3d.h>

void	init_master_struct_continue(t_all *t)
{
	t->pressed.key_w = 0;
	t->pressed.key_a = 0;
	t->pressed.key_s = 0;
	t->pressed.key_d = 0;
	t->pressed.key_arrow_bottom = 0;
	t->pressed.key_arrow_top = 0;
	t->pressed.key_arrow_left = 0;
	t->pressed.key_arrow_right = 0;
}

t_all	*initialize_master_struct(int fd)
{
	t_all	*t;

	if (!(t = malloc(sizeof(t_all))))
		exit_with_message("t_all init: malloc error!", 0);
	t->map = 0;
	t->maze = 0;
	t->plr = 0;
	t->spr = 0;
	t->spr_len = 0;
	if (!(t->maze = malloc(sizeof(t_maze_params))))
		maze_error("t_all init maze: malloc error!", t, 0, fd);
	t->maze->w_h[0] = -1;
	t->maze->w_h[1] = -1;
	t->maze->c_f[0] = 16777216;
	t->maze->c_f[1] = 16777216;
	ft_bzero(t->maze->textures, 5 * sizeof(char *));
	ft_bzero(t->txt_img, 5 * sizeof(void *));
	if (!(t->plr = malloc(sizeof(t_plr))))
		maze_error("t_all init plr: malloc error!", t, 0, fd);
	t->plr->x = -1;
	t->plr->y = -1;
	t->plr->vertical = 0;
	init_master_struct_continue(t);
	return (t);
}

void	init_txt_array(t_all *t)
{
	int	i;
	int	width;
	int	height;

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

void	init_game(t_all *t)
{
	int rubbish[3];
	int screen_w_h[2];

	mlx_get_screen_size(screen_w_h, screen_w_h + 1);
	if (screen_w_h[0] < t->maze->w_h[0])
		t->maze->w_h[0] = screen_w_h[0];
	if (screen_w_h[1] < t->maze->w_h[1])
		t->maze->w_h[1] = screen_w_h[1];
	if (!(t->game.mlx = mlx_init()))
		exit_with_message("GAME: mlx_init malloc error", t);
	if (!(t->game.img = \
			mlx_new_image(t->game.mlx, t->maze->w_h[0], t->maze->w_h[1])))
		exit_with_message("GAME: mlx_image_init malloc error", t);
	t->game.addr = (unsigned int *)(mlx_get_data_addr(t->game.img, rubbish,\
				rubbish + 1, rubbish + 2));
	t->game.win = 0;
	init_txt_array(t);
	fill_image_by_game(t);
}

void	init_draw_vars(t_draw *d, t_all *t)
{
	d->pos_x = t->plr->x;
	d->pos_y = t->plr->y;
	d->dir_x = t->plr->dir_x;
	d->dir_y = t->plr->dir_y;
	d->plane_x = t->plr->plane_x;
	d->plane_y = t->plr->plane_y;
	d->width = t->maze->w_h[0];
	d->height = t->maze->w_h[1];
	d->vert_pos = t->plr->vertical * d->height / 2;
	d->x = 0;
}
