/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:32:51 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 15:13:58 by mchau            ###   ########.fr       */
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
	t->max_x = -1;
	t->max_y = -1;
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
	exit_with_messsage(str, t->result);
}

void	player_handler()
{
}

void	map_parser(int fd, t_all *result, char *line)
{
	int i;
	int j;
	s_spr_list *tmp;
	t_compose t;

	init_map_vars(&t, result);
	i = 1;
	while (i)
	{
		j = 0;
		while (line[j])
		{
			if (IS_PLR_CHAR(line[j]))
			{
				if (t.result->plr->dir >= 0)
					map_error("MAP: More than one player", &t, line);
				t.result->plr->dir = (int)line[j];
				t.result->plr->x = i;
				t.result->plr->y = j;
			}
			else if (line[j] == '2')
			{
				if (!(tmp = malloc(sizeof(s_spr_list))))
					map_error("MAP: Error on spr malloc", &t, line);
				tmp->coords = i * 1000 + j;
				tmp->next = t.spr_struct;
				t.spr_struct = tmp;
			}
			else if (!IS_MAP_CHAR(line[j]))
				 map_error("MAP: Unknown symbol", &t, line);
			j++;
		}
		ft_lstadd_back(&(t.map_struct), ft_lstnew(line));
		t.max_x++;
		t.max_y = t.max_y < j ? j : t.max_y;
		if ((i = get_next_line(fd, &line)) == -1)
			map_error("MAP: GNL error!", &t, 0);
	}
	sprite_array_maker(&t);
	map_maker(&t);
	flood_fill(&t, t.result->plr->x, t.result->plr->y);
}

void	sprite_array_maker(t_compose *t)
{
	t_spr_struct	*spr;
	t_spr_struct	*tmp;
	int i;

	tmp = t->spr_struct;
	spr = t->spr_struct;
	while (tmp && (t->result->spr_len++) > -1)
		tmp = tmp->next;
	if (!(t->result->spr = malloc(sizeof(int) * t->result->spr_len)))
		map_error("MAP: sprite array maker error!", &t, 0);
	i = 0;
	while (spr)
	{
		t->result->spr[i] = spr->coords;
		i++;
		tmp = spr;
		spr = spr->next;
		free(tmp);
	}
}

void	map_maker(t_compose *t)
{
	t_list *tmp;
	t_list *chain;
	int i;
	int j;

	i = 0;
	tmp = t->map_struct;
	chain = t->map_struct;
	if (!(t->result->map = malloc(sizeof(char **) * t->max_x + 1)))
		map_error("MAP: map maker error!", &t, 0);
	t->result->map[t->max_x] = 0;
	while (chain)
	{
		if (!(t->result->map[i] = malloc(sizeof(char *) * t->max_y + 1)))
		{
			i--;
			while (i-- >= 0)
				free(t->result->map[i]);
			free(t->result->map);
			t->result->map = 0;
			map_error("MAP: map maker error 2!", &t, 0);
		}
		t->result->map[i][t->max_y] = 0;
		j = 0;
		while (t->chain->content[j])
			t->result->map[i][j] = t->chain->content[j++];
		while (j < t->max_y)
			t->result->map[i][j++] = ' ';
		i++;
		tmp = chain;
		chain = chain->next;
		free(tmp->content);
		free(tmp);
	}
}
