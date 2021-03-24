/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/03/24 13:54:53 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	free_wrapper(t_all *t)
{
	int i;

	if (t)
	{
		if (t->plr)
			free(t->plr);
		if (t->maze)
		{
			i = 0;
			while (i < 5)
			{
				if (t->maze->textures[i])
					free(t->maze->textures[i]);
				if (t->txt_img[i])
					free(t->txt_img[i]);
				i++;
			}
			free(t->maze);
		}
		if (t->spr)
			free(t->spr);
		if (t->map)
		{
			i = 0;
			while (t->map[i])
				free(t->map[i++]);
		}
		free(t);
	}
}

void	exit_with_message(char *str, t_all *t)
{
	write(1, "Error\n", 6);
	free_wrapper(t);
	if (str)
		ft_putstr(str);
	exit(0);
}

int		main(int argc, char **argv)
{
	int				i;
	int				fd;
	t_all			*t;

	if (argc < 2)
		exit_with_message("Map file is missing\n", 0);
	i = 0;
	while (*(argv[1] + i) != 0)
		i++;
	if (i < 4 || IS_NOT_TRUE_FORMAT(i - 1))
		exit_with_message("Invalid map format\n", 0);
	errno = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_message(strerror(errno), 0);
	t = map_file_parser(fd); // забываешь всюду закрыть fd в случае парсинга;
	close(fd);
	init_game(t);
	if (argc >= 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		bmp_maker(t);
	else
		go_game_logic(t);

	free_wrapper(t);
	//чисти все при --save и escape/[x]
	return (0);
}
