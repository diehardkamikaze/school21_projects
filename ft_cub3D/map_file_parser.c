/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:28:18 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 11:01:23 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	initialize_struct(t_all *t)
{
	t->map = 0;
	t->plr = 0;
	t->maze->w_h[0] = 0;
	t->maze->w_h[1] = 0;
	t->maze->c_f[0] = -1;
	t->maze->c_f[1] = -1;
	t->maze->no_txt = -1;
	t->maze->we_txt = -1;
	t->maze->ea_txt = -1;
	t->maze->so_txt = -1;
	t->maze->sprite_txt = -1;
}

int		r_handler(char *line, t_all *t)
{
	char	*endptr;
	long	tmp;
	int		i;

	if (t->maze->w_h[0] > 0)
		exit_with_message("R parameter is repeating!", t);
	i = 0;
	endptr = line;
	while (i < 2)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (tmp == 0 && endptr == line)
			exit_with_message("reso:enter values!", t);
		if (tmp <= 0)
			exit_with_message("reso:invalid value!", t);
		if (tmp > INT_MAX)
			exit_with_message("reso:integer value overflow!", t);
		t->maze->w_h[i] = (int)tmp;
		i++;
	}
	if (*endptr != 0)
		exit_with_message("Bag characters after line!", t);
	return (1);
}

int		colors_handler(char below, char *line, t_all *t)
{
	int		index;
	long	tmp;
	int		comma;
	char	*endptr;

	index = (below == 'C' ? 0 : 1);
	if (t->maze->c_f[index] >= 0)
		exit_with_message("C or F parameter is repeating!", t);
	t->maze->c_f[index] = 0;
	comma = 0;
	tmp = 0;
	endptr = line;
	while (comma <= 2)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (tmp == 0 && endptr == line)
			exit_with_message("color: enter values!", t);
		if (tmp > 255)
			exit_with_message("color: value overflow!", t);
		if (comma < 2)
		{
			ft_strtol(endptr, &endptr, 10);
			if (*endptr != ',')
				exit_with_message("color: where is comma!?", t);
			endptr++;
		}
		t->maze->c_f[index] += (int)tmp << ((8 * (2 - comma)));
		comma++;
	}
	if (*endptr != 0)
		exit_with_message("Bag characters after line!", t);
	return (1);
}

int		textures_handler(char character, char *line, t_all *t)
{
	int		fd;
	int		*path_ptr;

	path_ptr = 0;
	if (character == 'E')
		path_ptr = &(t->maze->ea_txt);
	if (character == 'W')
		path_ptr = &(t->maze->we_txt);
	if (character == 'N')
		path_ptr = &(t->maze->no_txt);
	if (character == 'O')
		path_ptr = &(t->maze->so_txt);
	if (character == 'S')
		path_ptr = &(t->maze->sprite_txt);
	if (*path_ptr != -1)
		exit_with_message("Some texture parameter is repeating!", t);
	while (IS_SPACE(*line))
		line++;
	errno = 0;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		exit_with_message(strerror(errno), 0);
	*path_ptr = fd;
	// здесь сразу как-то выделяем память и считываем структуру а пока просто проверка?
	// пути хранить нам, наверное и не понадобится
	close(fd);
	return (1);
}

t_all	*map_file_parser(int fd)
{
	char	*line;
	t_all	*result;
	int		counter;
	int		i;

	counter = 0;
	if (!(result = malloc(sizeof(t_all))))
		exit_with_message("malloc error!", 0);
	if (!(result->maze = malloc(sizeof(t_maze_params))))
		exit_with_message("malloc error!", result);
	initialize_struct(result);
	//all initialing function

	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1)
			return exit_with_message("malloc error in GNL!", result);
		if (line[0] == 0)
			continue;
		if (line[0] == 'R' && IS_SPACE(line[1]))
			counter += r_handler(line + 1, result); //добавить чистку line
		else if ((line[0] == 'F' || line[0] == 'C') && IS_SPACE(line[1]))
			counter += colors_handler(line[0], line + 1, result);  //добавить чистку line
		else if (line[0] == 'S')
		{
			if (IS_SPACE(line[1]))
				counter += textures_handler(line[0], line + 2, result);  //добавить чистку line
			else if (line[1] == 'O' && IS_SPACE(line[2]))
				counter += textures_handler('O', line + 3, result);  //добавить чистку line
		}
		else if ((!ft_strncmp("NO", line, 2) || !ft_strncmp("WE", line, 2) \
			|| !(ft_strncmp("EA", line, 2))) && IS_SPACE(line[2]))
			counter += textures_handler(line[0], line + 3, result);  //добавить чистку line
		else if (counter < 8)
			exit_with_message("unknown parameter symbol", result);  //добавить чистку line
		else
			break;
		free(line);
		line = 0;
	}
	if (line == 0)
		if (counter < 8)
			exit_with_message("insufficient number of parameters", result);
		else
			exit_with_message("map is missing", result);
	map_parser(fd, result, line);
	return (result);
}
