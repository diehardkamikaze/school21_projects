/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/03/18 09:18:00 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
/*
void	exit_with_message(char *str, t_map_params *t)
{
	// дополнишь если что
	write(1, "Error\n", 6);
	if (t)
		free(t);
	ft_putstr(str);
}
*/
int main(/*int argc, char **argv*/)
{
/*	int				i;
	int				fd;
	t_maze_params	t;

	if (argc < 2)
	{
		error_message("Map file is missing\n");
		return (0);
	}
	i = 0;
	while (*(argv[1] + i) != 0)
		i++;
	while (is_space(*(argv[1] + i - 1)))
		i--;
	argv[1][i + 1] == '\0'; // это не повлияет на free?
	if (!(i >= 3 && argv[1][i] == 'b' &&
			argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
			&& argv[1][i - 3] == '.'))
		error_message("Invalid map format\n");
	errno = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_message(strerror(errno));
	if(!t = malloc(t_maze_params))
		error_message("Problem with malloc");
	map_parser(fd, t);
	//close(fd) into map_parser??! after reading? into parser?
*/	return (0);
}
