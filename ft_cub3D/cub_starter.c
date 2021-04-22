/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 18:00:23 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		is_not_true_format(char **argv, int val)
{
	if (argv[1][val] != 'b' || argv[1][val - 1] != 'u' || \
			argv[1][val - 2] != 'c' || argv[1][val - 3] != '.')
		return (1);
	return (0);
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
	if (i < 4 || is_not_true_format(argv, i - 1))
		exit_with_message("Invalid map format\n", 0);
	errno = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_message(strerror(errno), 0);
	t = map_file_parser(fd);
	init_game(t);
	if (argc >= 3 && ft_strncmp(argv[2], "--save", 6) == 0 && argv[2][6] == 0)
		bmp_maker(t);
	else
		go_game_logic(t);
	return (0);
}
