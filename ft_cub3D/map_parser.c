/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:36:44 by mchau             #+#    #+#             */
/*   Updated: 2021/03/18 13:41:57 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	initialize_struct(t_all *t)
{
	t->maze->w_h[0] = 0;
	t->maze->w_h[1] = 0;
	t->maze->c_f[0] = -1;
	t->maze->c_f[1] = -1;
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

t_all	*map_parser(int fd)
{
	char	*line;
	t_all	*result;
	int		counter;

	counter = 0;
	if (!(result = malloc(sizeof(t_all))))
		exit_with_message("malloc error!", 0);
	if (!(result->maze = malloc(sizeof(t_maze_params))))
		exit_with_message("malloc error!", result);
	initialize_struct(result);
	//all initialing function

	while (get_next_line(fd, &line))
	{
		if (line[0] == 0)
			continue;
		if (line[0] == 'R' && IS_SPACE(line[1]))
			counter += r_handler(line + 1, result);
		else if ((line[0] == 'F' || line[0] == 'C') && IS_SPACE(line[1]))
			counter += colors_handler(line[0], line + 1, result);
		else
			exit_with_message("undefined parameter", result);
	}
	return (result);
}

