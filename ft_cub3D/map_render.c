/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:41:58 by mchau             #+#    #+#             */
/*   Updated: 2021/03/29 10:29:15 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

/*
 * border_size is define in px
 * 4 cells top,bot,left,right from player position square
 * if min px / 4 + 10px < 19px -> does not render
 */
/*
void	render_square(unsigned int *img, int coord_x, int coord_y, int x_len, int y_len)
{
	int j;

	while (from_y < to_y)
	{
		j = from_x;
		while (j < to_x)
		{
			img[from_y + j] = 0xffb5c5;
			j++;
		}
		from_y+=w;
	}
}

int		render_cells(t_all *t, img, int cell_size, int x, int y)
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	start_x = t->plr->x - 4;
	end_x = t->plr->x + 4;
	end_y = t->plr->y + 4;
	while (start_x <= end_x)
	{
		start_y = t->plr->y - 4;
		while(start_y <= end_y)
		{
			if (t->map[start_x][start_y] == 'S')
				render_square(img, y + start_y % 9 , y + start_y % 9 + cell_size, x + start_x % 9, x + start_x % 9 + cell_size, int w)
			end_y++;
		}
		start_x++;
	}
}

int		render_map(t_all *t)
{
	int	width;
	int	height;
	unsigned int *img;
	int	min;
	int	cell_size;
	int from;
	int to;

	img = (unsigned int *)mlx_get_data_addr_main(t->game.img, &width, &height);
	min = width > height ? height : width;
	if (min / 4 + 20 < 19)
		return 0;
	cell_size = min / 4 / 9;
	from = height;
	to = height - min / 4 + 10;
	render_square(img, (height - 10) * width, (height - 1) * width, 0, 20 + cell_size * 9, width);
	render_square(img, (height - 10 - cell_size * 9)  * width, (height - 10) * width, 0, 10, width);
	render_square(img, (height - 10 - cell_size * 9)  * width, (height - 10) * width, cell_size * 9 + 10, cell_size * 9 + 20, width);
	render_square(img, (height - 20 - cell_size * 9) * width, (height - 10 - cell_size * 9) * width, 0,  20 + cell_size * 9, width);
	
	return (1);
}*/
