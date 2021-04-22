/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:45:49 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:56:44 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cub3d.h>

void	draw_objects(t_all *t, t_draw *d, double *z_buffer)
{
	int		i;
	int		sprite_order[t->spr_len];
	double	sprite_distance[t->spr_len];

	i = 0;
	while (i < t->spr_len)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((d->pos_x - (t->spr[i] / 1000 + 0.5)) * \
		(d->pos_x - (t->spr[i] / 1000 + 0.5)) + (d->pos_y - (t->spr[i] % 1000\
				+ 0.5)) * (d->pos_y - (t->spr[i] % 1000 + 0.5)));
		i++;
	}
	sort_all_sprites(sprite_order, sprite_distance, t->spr_len);
	i = 0;
	while (i < t->spr_len)
	{
		if (sprite_distance[i] > 0.125)
			draw_sprite(t, d, sprite_order[i], z_buffer);
		i++;
	}
}

void	continue_init_sprite(t_all *t, t_draw *d, t_draw_spr *spr)
{
	spr->draw_start_x = -spr->sprite_width / 2 + spr->spr_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->spr_screen_x;
	if (spr->draw_end_x >= d->width)
		spr->draw_end_x = d->width - 1;
	spr->texture = (unsigned int *)(mlx_get_data_addr_main(t->txt_img[SPR_TXT],\
				&(spr->tex_width), &(spr->tex_height)));
}

void	init_current_sprite(t_all *t, t_draw *d, t_draw_spr *spr)
{
	spr->inv_det = 1.0 / (d->plane_x * d->dir_y - d->dir_x * d->plane_y);
	spr->transform_x = spr->inv_det * (d->dir_y * \
			spr->sprite_x - d->dir_x * spr->sprite_y);
	spr->transform_y = spr->inv_det * (-d->plane_y * \
			spr->sprite_x + d->plane_x * spr->sprite_y);
	spr->spr_screen_x = (int)((d->width / 2) * (1 + \
				spr->transform_x / spr->transform_y));
	spr->move_screen = d->vert_pos;
	spr->sprite_height = abs((int)(d->width * 0.75 / (spr->transform_y)));
	spr->sprite_width = spr->sprite_height;
	spr->draw_start_y = -spr->sprite_height / 2 + d->height / 2\
						+ spr->move_screen;
	spr->draw_end_y = spr->sprite_height / 2 +\
		d->height / 2 + spr->move_screen;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	if (spr->draw_start_y >= d->height - 1)
		spr->draw_start_y = d->height - 1;
	if (spr->draw_end_y >= d->height)
		spr->draw_end_y = d->height - 1;
	if (spr->draw_end_y < 0)
		spr->draw_end_y = 0;
	continue_init_sprite(t, d, spr);
}

void	draw_sprite_vertical(t_all *t, t_draw *d, t_draw_spr *spr,
		t_tex_coords *m)
{
	int		j;
	int		tmp;
	int		color;

	j = spr->draw_start_y;
	while (j < spr->draw_end_y)
	{
		tmp = (j - spr->move_screen) * 256 - d->height * 128 +\
		spr->sprite_height * 128;
		m->tex_y = ((tmp * spr->tex_height) / spr->sprite_height) / 256;
		if (spr->tex_width * m->tex_y + m->tex_x < 0 && (j += 1))
			continue;
		color = spr->texture[spr->tex_width * m->tex_y + m->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			t->game.addr[j * d->width + m->line] = color;
		j++;
	}
}

void	draw_sprite(t_all *t, t_draw *d, int order, double *z_buffer)
{
	t_draw_spr		spr;
	t_tex_coords	m;

	spr.sprite_x = (t->spr[order] / 1000) + 0.5 - d->pos_x;
	spr.sprite_y = (t->spr[order] % 1000) + 0.5 - d->pos_y;
	init_current_sprite(t, d, &spr);
	m.line = spr.draw_start_x;
	while (m.line < spr.draw_end_x)
	{
		m.tex_x = (int)(256 * (m.line - (-spr.sprite_width / 2 +\
			spr.spr_screen_x)) * spr.tex_width / spr.sprite_width) / 256;
		if (spr.transform_y > 0 && m.line > 0 && m.line < d->width &&\
			spr.transform_y < z_buffer[m.line])
		{
			draw_sprite_vertical(t, d, &spr, &m);
		}
		m.line += 1;
	}
}
