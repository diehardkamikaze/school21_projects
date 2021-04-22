/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:28:18 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:55:07 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		r_handler(char *line, t_all *t, int fd)
{
	char	*endptr;
	long	tmp;
	int		i;

	if (t->maze->w_h[0] != -1)
		maze_error("R parameter is repeating!", t, line, fd);
	i = 0;
	endptr = line + 2;
	while (i < 2)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (tmp <= 0)
			maze_error("reso:invalid value!", t, line, fd);
		if (tmp > INT_MAX)
			maze_error("reso:integer value overflow!", t, line, fd);
		t->maze->w_h[i] = (int)tmp;
		i++;
	}
	if (*endptr != 0)
		maze_error("reso: Bad characters after line!", t, line, fd);
	return (1);
}

int		colors_handler(int index, char *line, t_all *t, int fd)
{
	long	tmp;
	int		comma;
	char	*endptr;

	endptr = line + 2;
	if (!(comma = 0) && t->maze->c_f[index] != 16777216)
		maze_error("C or F parameter is repeating!", t, line, fd);
	while (comma < 3)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (!(tmp >= 0 && tmp <= 255))
			maze_error("color: invalid value!", t, line, fd);
		if (comma < 2)
		{
			if (0 == ft_strtol(endptr, &endptr, 10) && *endptr != ',')
				maze_error("color: where is comma!?", t, line, fd);
			endptr++;
		}
		t->maze->c_f[index] += (int)tmp << ((8 * (2 - comma)));
		comma++;
	}
	if (*endptr != 0)
		maze_error("color: Bad characters after line!", t, line, fd);
	return (1);
}

int		textures_handler(char character, char *line, t_all *t, int fd)
{
	int		current_tex;
	char	*endptr;

	endptr = line + 2;
	if (!(errno = 0) && character == 'E')
		current_tex = EA_TXT;
	if (character == 'W')
		current_tex = WE_TXT;
	if (character == 'N')
		current_tex = NO_TXT;
	if (character == 'O')
		current_tex = SO_TXT;
	if (character == 'S')
		current_tex = SPR_TXT;
	if (t->maze->textures[current_tex] != 0)
		maze_error("Some texture parameter is repeating!", t, line, fd);
	while (IS_SPACE(*endptr))
		endptr++;
	t->maze->textures[current_tex] = ft_strdup(endptr);
	if (!(t->maze->textures[current_tex]))
		maze_error(strerror(errno), t, line, fd);
	return (1);
}

int		map_file_parser_iteration(int fd, int *counter,\
		char *line, t_all *result)
{
	if (line[0] != 0)
	{
		if (line[0] == 'R' && IS_SPACE(line[1]))
			*counter += r_handler(line, result, fd);
		else if ((line[0] == 'F' || line[0] == 'C') && IS_SPACE(line[1]))
			*counter += colors_handler(line[0] == 'F', line, result, fd);
		else if (line[0] == 'S')
		{
			if (IS_SPACE(line[1]))
				*counter += textures_handler(line[0], line, result, fd);
			else if (line[1] == 'O' && IS_SPACE(line[2]))
				*counter += textures_handler('O', line, result, fd);
		}
		else if ((!ft_strncmp("NO", line, 2) || !ft_strncmp("WE", line, 2) \
			|| !(ft_strncmp("EA", line, 2))) && IS_SPACE(line[2]))
			*counter += textures_handler(line[0], line, result, fd);
		else if (*counter < 8)
			maze_error("unknown parameter symbol", result, line, fd);
		else
			return (1);
	}
	return (0);
}

t_all	*map_file_parser(int fd)
{
	char	*line;
	t_all	*result;
	int		counter;
	int		i;

	counter = 0;
	result = initialize_master_struct(fd);
	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1)
			maze_error("malloc error in GNL!", result, 0, fd);
		if (line[0] != 0)
		{
			if (map_file_parser_iteration(fd, &counter, line, result))
				break ;
		}
		free(line);
		line = 0;
	}
	if (counter < 8)
		exit_with_message("insufficient number of parameters", result);
	map_parser(fd, result, line);
	return (result);
}
