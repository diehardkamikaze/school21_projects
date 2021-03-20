/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:32:51 by mchau             #+#    #+#             */
/*   Updated: 2021/03/20 08:07:25 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	init_map_vars(t_compose *t, t_all *result)
{
	t->result = result;
	if (!(t->result->plr = malloc(sizeof(t_plr))))
		exit_with_message("Malloc error in init_map: plr_struct", t->result);
	t->result->plr->dir = -1;
	t->map_struct = 0;
	t->spr_struct = 0;
	t->max_x = 0;
	t->max_y = 0;
}

void	map_error(char *str, t_compose *t, char *line)
{
	t_spr_list *tmp;

	if (line)
		free (line);
	ft_lstclear(&(t->map_struct));
	while (t->spr_struct)
	{
		tmp = t->spr_struct;
		t->spr_struct = t->spr_struct->next;
		free (tmp);
	}
	exit_with_message(str, t->result);
}

void	player_handler(int i, int j, t_compose *t, char *line)
{
	if (t->result->plr->dir >= 0)
		map_error("MAP: More than one player", t, line);
	t->result->plr->dir = (int)line[j];
	t->result->plr->x = i;
	t->result->plr->y = j;
}

void	sprite_handler(int coords, t_compose *t, char *line)
{
	t_spr_list *tmp;

	if (!(tmp = malloc(sizeof(t_spr_list))))
		map_error("MAP: Error on spr malloc", t, line);
	tmp->coords = coords;
	tmp->next = t->spr_struct;
	t->spr_struct = tmp;
}

void	map_parser_iteration(int i, char *line, t_compose *t)
{
	int j;

	j = 0;
	if (line[j] == 0)
		map_error("MAP: empty line", t, line);
	while (line[j])
	{
		if (IS_PLR_CHAR(line[j]))
			player_handler(i, j, t, line);
		else if (line[j] == '2')
			sprite_handler(1000 * t->max_x + j, t, line);
		else if (!IS_MAP_CHAR(line[j]))
			map_error("MAP: Unknown symbol", t, line);
		j++;
	}
	ft_lstadd_back(&(t->map_struct), ft_lstnew(line));
	t->max_x++;
	t->max_y = t->max_y < j ? j : t->max_y;
}

void	map_parser(int fd, t_all *result, char *line)
{
	int i;
	t_compose t;

	init_map_vars(&t, result);
	i = 1;
	while (i)
	{
		map_parser_iteration(i, line, &t);
		if ((i = get_next_line(fd, &line)) == -1)
			map_error("MAP: GNL error!", &t, 0);
	}
	map_parser_iteration(i, line, &t);
	if (t.result->plr->x <= 0)
		map_error("MAP: no player on map", &t, line);
	sprite_array_maker(&t);
	map_maker(&t);
	flood_fill(&t, t.result->plr->x, t.result->plr->y);// если что ты тут флоатами оперируешь :D
}
