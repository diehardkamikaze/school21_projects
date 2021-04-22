/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:36:13 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 19:05:11 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

unsigned int	get_color(int el, unsigned int *addr)
{
	return (addr[el]);
}

void			bitmap_bmp_meta(int fd, t_all *t, int offset)
{
	unsigned char	meta[54];
	int				width;
	int				height;

	bzero(meta, 54);
	width = (int)t->maze->w_h[0];
	height = (int)t->maze->w_h[1];
	meta[0] = 0x42;
	meta[1] = 0x4d;
	*(int *)(meta + 2) = (width * 3 + offset) * height + 54;
	meta[10] = 0x36;
	meta[14] = 0x28;
	*(int *)(meta + 18) = width;
	*(int *)(meta + 22) = height;
	meta[26] = 0x1;
	meta[28] = 0x18;
	errno = 0;
	if (write(fd, meta, 54) == -1)
	{
		close(fd);
		exit_with_message(strerror(errno), t);
	}
}

void			bitmap_bmp_pixels(int fd, t_all *t, int offset)
{
	int		height;
	int		width;
	int		i;
	char	adding[4];

	width = (int)t->maze->w_h[0];
	height = (int)t->maze->w_h[1];
	while (--height >= 0 && !(i = 0))
	{
		while (i < width)
		{
			*(unsigned int *)adding = get_color(height * width + i,
					t->game.addr);
			if ((i += 1) && write(fd, adding, 3) == -1)
			{
				close(fd);
				exit_with_message(strerror(errno), t);
			}
		}
		if ((offset > 0) && write(fd, "\0\0\0", offset) == -1)
		{
			close(fd);
			exit_with_message(strerror(errno), t);
		}
	}
}

void			bmp_maker(t_all *t)
{
	int fd;
	int he;
	int wi;
	int offset;

	errno = 0;
	fd = open("sceenshot.bmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if (fd == -1)
		exit_with_message(strerror(errno), t);
	he = t->maze->w_h[1];
	wi = t->maze->w_h[0];
	offset = (4 - ((int)t->maze->w_h[0] * 3) % 4) % 4;
	bitmap_bmp_meta(fd, t, offset);
	bitmap_bmp_pixels(fd, t, offset);
	close(fd);
	exit_handler(t);
}
