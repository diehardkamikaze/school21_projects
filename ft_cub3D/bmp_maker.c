/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:36:13 by mchau             #+#    #+#             */
/*   Updated: 2021/03/21 14:06:03 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

typedef union	u_bm {
	int	num;
	char c[4];
}				t_bm;

void	bitmap_file_header(int fd, t_all *t)
{
	t_bm tmp;

	tmp.c[0] = 0x42;
	tmp.c[1] = 0x4d;
	write (fd, tmp.c, 2);

	tmp.num = (t->maze->w_h / 1000000 * 4) * t->maze->w_h % 1000000 + 54; // filesize

	write(fd, tmp.c, 4);
	tmp.num = 0;
	write(fd, tmp.c, 4);
	write(fd, tmp.c, 2);
	write(fd, tmp.c, 2);
	tmp.num = 0x36; //pixeDataOffset
	write(fd, tmp.c, 4);
	tmp.num = 40; // HeaderSize
	write(fd, tmp.c, 4);
	tmp.num = t->maze->w_h / 1000000; // img width
	write(fd, tmp.c, 4);
	tmp.num = t->maze->w_h % 1000000; // img height
	write(fd, tmp.c, 4);
	tmp.num = 1; //color plane?
	write(fd, tmp.c, 4);
	tmp.num = 32;// BitsPerPixel
	write(fd, tmp.c, 4);
	tmp.num = 0;
	write(fd, tmp.c, 4);
	write(fd, tmp.c, 4);
	write(fd, tmp.c, 4);
	write(fd, tmp.c, 4);

}

void	bmp_maker(t_all *t)
{
	int fd;
	t_bm tmp;
	tmp.num = 0;
	// не забывай закрывать fd при ошибках
	// возможно красивый вывод этапов на экран?
	fd = open("sceenshot.bmp", O_CREAT | O_TRUNC | O_WRONLY , S_IRWXU);
	if (fd == -1)
		exit_with_message("SAVE: Can't work with file", t);
	// сохранение различных хедеров
	//BITMAPFILEHEADER + BITMAPINFOHEADER + COLOR TABLE;
	bitmap_file_header(fd, t);
	//BITMAPINFOHEADER
	//COLOR TABLE

	/* pixel_data(fd); */
	int i = 0;
	int hei = t->maze->w_h % 1000000;
	int wei = (t->maze->w_h / 1000000);
	while (hei-- && !(i = 0))
		while (i < wei)
		{
			write(fd, tmp.c, 4);
			i++;
		}
	close(fd);
}
