/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:32:51 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:55:40 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		player_handler(int i, int j, t_compose *t, char *line)
{
	t_plr	*plr;

	plr = t->result->plr;
	if ((plr->y = (double)j + 0.5) && plr->x != -1)
		return (0);
	plr->x = (double)i + 0.5;
	plr->plane_x = 0.0;
	plr->plane_y = 0.66;
	plr->dir_x = -1.0;
	plr->dir_y = 0.0;
	if (line[j] == 'E' && (plr->plane_x = 0.66))
	{
		plr->plane_y = 0;
		plr->dir_x = 0.0;
		plr->dir_y = 1.0;
	}
	if (line[j] == 'W' && (plr->plane_x = -0.66))
	{
		plr->plane_y = 0;
		plr->dir_x = 0.0;
		plr->dir_y = -1.0;
	}
	if (line[j] == 'S' && (plr->dir_x = 1.0))
		plr->plane_y = -0.66;
	return (1);
}

void	map_parser_iteration(char *line, t_compose *t, int fd)
{
	int j;

	j = 0;
	if (line[j] == 0)
		map_error("MAP: empty line", t, line, fd);
	while (line[j])
	{
		if (IS_PLR_CHAR(line[j]))
		{
			if (!player_handler(t->max_x, j, t, line))
				map_error("MAP: More than one player", t, line, fd);
		}
		else if (!IS_ALLOWED_CHAR(line[j]))
			map_error("MAP: Unknown symbol", t, line, fd);
		j++;
	}
	ft_lstadd_back(&(t->map_struct), ft_lstnew(line));
	t->max_x++;
	t->max_y = t->max_y < j ? j : t->max_y;
}

void	init_map_vars(t_compose *t, t_all *result)
{
	t->result = result;
	t->map_struct = 0;
	t->spr_struct = 0;
	t->max_x = 0;
	t->max_y = 0;
}

void	map_parser(int fd, t_all *result, char *line)
{
	int			i;
	t_compose	t;

	init_map_vars(&t, result);
	i = 1;
	while (i)
	{
		map_parser_iteration(line, &t, fd);
		if ((i = get_next_line(fd, &line)) == -1)
			map_error("MAP: GNL error!", &t, 0, fd);
	}
	map_parser_iteration(line, &t, fd);
	close(fd);
	if (t.result->plr->x == -1)
		map_error("MAP: no player on map", &t, line, -1);
	map_array_maker(&t);
	flood_fill(&t, (int)t.result->plr->x, (int)t.result->plr->y);
	sprite_array_maker(&t);
}
