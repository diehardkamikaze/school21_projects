/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:28:18 by mchau             #+#    #+#             */
/*   Updated: 2021/03/23 16:08:35 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	maze_error(char *str, t_all *t, char *line)
{
	if (line)
		free(line);
	exit_with_message(str, t);
}

t_all	*initialize_struct(void)
{
	t_all *t;

	if (!(t = malloc(sizeof(t_all))))
		exit_with_message("t_all init: malloc error!", 0);
	t->map = 0;
	t->maze = 0;
	t->plr = 0;
	t->spr = 0;
	t->spr_len = 0;
	if (!(t->maze = malloc(sizeof(t_maze_params))))
		maze_error("t_all init maze: malloc error!", t, 0);
	t->maze->w_h = 0;
 	t->maze->c_f[0] = -1;
 	t->maze->c_f[1] = -1;
	ft_bzero(t->maze->textures, 5 * sizeof(char *));
	ft_bzero(t->txt_img, 5 * sizeof(void *));
	if (!(t->plr = malloc(sizeof(t_plr))))
		maze_error("t_all init plr: malloc error!", t, 0);
	t->plr->x = 0;
	t->plr->y = 0;
	t->pressed.key_w = 0;
	t->pressed.key_a = 0;
	t->pressed.key_s = 0;
	t->pressed.key_d = 0;
	t->pressed.key_arrow_left = 0;
	t->pressed.key_arrow_right = 0;
    return (t);
}

int		r_handler(char *line, t_all *t)
{
	char	*endptr;
	long	tmp;
	int		i;

	if (t->maze->w_h > 0)
		maze_error("R parameter is repeating!", t, line);
	i = 0;
	endptr = line + 2;
	while (i < 2)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (tmp <= 0)
			maze_error("reso:invalid value!", t, line);
		if (tmp > INT_MAX)
			maze_error("reso:integer value overflow!", t, line);
		t->maze->w_h = t->maze->w_h * 1000000 + (int)tmp;
		i++;
	}
	if (*endptr != 0)
		maze_error("reso: Bad characters after line!", t, line);
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
		maze_error("C or F parameter is repeating!", t, line);
	comma = 0;
	tmp = 0;
	endptr = line + 2;
	while (comma <= 2)
	{
		tmp = ft_strtol(endptr, &endptr, 10);
		if (tmp < 0)
			maze_error("color: invalid values!", t, line);
		if (tmp > 255)
			maze_error("color: value overflow!", t, line);
		if (comma < 2)
		{
			if (*endptr != ',' && 0 == ft_strtol(endptr, &endptr, 10))
				maze_error("color: where is comma!?", t, line);
			endptr++;
		}
		t->maze->c_f[index] += (int)tmp << ((8 * (2 - comma)));
		comma++;
	}
	if (*endptr != 0)
		maze_error("color: Bad characters after line!", t, line);
	return (1);
}

int		textures_handler(char character, char *line, t_all *t)
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
		maze_error("Some texture parameter is repeating!", t, line);
	while (IS_SPACE(*endptr))
		endptr++;
	t->maze->textures[current_tex] = ft_strdup(endptr);
	if (!(t->maze->textures[current_tex]))
		maze_error(strerror(errno), t, line);
	return (1);
}

t_all	*map_file_parser(int fd)
{
	char	*line;
	t_all	*result;
	int		counter;
	int		i;

	counter = 0;
	result = initialize_struct();
	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1)
			maze_error("malloc error in GNL!", result, 0);
		if (line[0] != 0)
		{
			if (line[0] == 'R' && IS_SPACE(line[1]))
				counter += r_handler(line, result);
			else if ((line[0] == 'F' || line[0] == 'C') && IS_SPACE(line[1]))
				counter += colors_handler(line[0], line, result);
			else if (line[0] == 'S')
			{
				if (IS_SPACE(line[1]))
					counter += textures_handler(line[0], line, result);
				else if (line[1] == 'O' && IS_SPACE(line[2]))
					counter += textures_handler('O', line, result);
			}
			else if ((!ft_strncmp("NO", line, 2) || !ft_strncmp("WE", line, 2) \
				|| !(ft_strncmp("EA", line, 2))) && IS_SPACE(line[2]))
				counter += textures_handler(line[0], line, result);
			else if (counter < 8)
				maze_error("unknown parameter symbol", result, line);
			else
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
