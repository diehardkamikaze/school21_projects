/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:18:53 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:50:38 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	free_wrapper(t_all *t)
{
	int i;

	if (t)
	{
		if (t->plr)
			free(t->plr);
		if (t->maze && !(i = 0))
		{
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
		if (t->map && !(i = 0))
			while (t->map[i])
				free(t->map[i++]);
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

void	maze_error(char *str, t_all *t, char *line, int fd)
{
	close(fd);
	if (line)
		free(line);
	exit_with_message(str, t);
}

void	map_error(char *str, t_compose *t, char *line, int fd)
{
	t_spr_list *tmp;

	if (fd != -1)
		close(fd);
	if (line)
		free(line);
	ft_lstclear(&(t->map_struct));
	while (t->spr_struct)
	{
		tmp = t->spr_struct;
		t->spr_struct = t->spr_struct->next;
		free(tmp);
	}
	exit_with_message(str, t->result);
}

void	map_malloc_error(int i, t_compose *t)
{
	while (i-- >= 0)
		free(t->result->map[i]);
	free(t->result->map);
	t->result->map = 0;
	map_error("MAP: map maker error 2!", t, 0, -1);
}
