/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_draws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:45:30 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:57:02 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cub3d.h>

unsigned int	*get_world_side_txt(t_all *t, t_draw *d, int *wi, int *hi)
{
	int num;

	if (d->raydir_x > 0 && d->raydir_y >= 0 && (num = SO_TXT) > -1)
		if (d->side == 1)
			num = EA_TXT;
	if (d->raydir_x >= 0 && d->raydir_y < 0 && (num = SO_TXT) > -1)
		if (d->side == 1)
			num = WE_TXT;
	if (d->raydir_x < 0 && d->raydir_y <= 0)
	{
		if (d->side == 1)
			num = WE_TXT;
		else
			num = NO_TXT;
	}
	if (d->raydir_x <= 0 && d->raydir_y > 0)
	{
		if (d->side == 1)
			num = EA_TXT;
		else
			num = NO_TXT;
	}
	return ((unsigned int *)mlx_get_data_addr_main(t->txt_img[num], wi, hi));
}

int				shadow_color(t_draw *d, int color)
{
	int	tmp_c;
	int	color_r;
	int	color_g;
	int	color_b;

	color_r = color / 256 / 256;
	tmp_c = color_r - (int)(d->wall_dist) * 2;
	if (tmp_c < 0)
		tmp_c = 0;
	color_r = tmp_c;
	color_g = color / 256 % 256;
	tmp_c = color_g - (int)(d->wall_dist) * 2;
	if (tmp_c < 0)
		tmp_c = 0;
	color_g = tmp_c;
	color_b = color % 256;
	tmp_c = color_b - (int)(d->wall_dist) * 2;
	if (tmp_c < 0)
		tmp_c = 0;
	color_b = tmp_c;
	return (color_r << 16 | color_g << 8 | color_b);
}

void			draw_ceil(t_draw *d, t_all *t)
{
	int i;
	int lim;

	i = 0;
	lim = d->draw_start;
	while (i < lim)
	{
		t->game.addr[i * d->width + d->x] = t->maze->c_f[0];
		i++;
	}
}

void			draw_texture(t_draw *d, t_all *t)
{
	t_draw_texture o;

	o.texture = get_world_side_txt(t, d, &o.tex_width, &o.tex_height);
	if (d->side == 0)
		o.wall_x = d->pos_y + d->wall_dist * d->raydir_y;
	else
		o.wall_x = d->pos_x + d->wall_dist * d->raydir_x;
	o.wall_x = o.wall_x - floor((o.wall_x));
	o.tex_x = (int)(o.wall_x * (double)(o.tex_width));
	if ((d->side == 0 && d->raydir_x > 0) || (d->side == 1 && d->raydir_y < 0))
		o.tex_x = o.tex_width - o.tex_x - 1;
	o.scale = 1.0 * o.tex_height / d->line_height;
	o.tex_start = (d->draw_start - (d->height / 2 - d->line_height / 2)\
		- d->vert_pos) * o.scale;
	while (d->draw_start < d->draw_end)
	{
		o.tex_y = (int)o.tex_start % (o.tex_height - 1);
		o.tex_start += o.scale;
		t->game.addr[d->draw_start * d->width + d->x] = \
				shadow_color(d, o.texture[o.tex_height * o.tex_y + o.tex_x]);
		d->draw_start++;
	}
}

void			draw_floor(t_draw *d, t_all *t)
{
	if (d->draw_end < 0)
		d->draw_end = 0;
	while (d->draw_end < d->height)
	{
		t->game.addr[d->draw_end * d->width + d->x] = t->maze->c_f[1];
		d->draw_end++;
	}
}
