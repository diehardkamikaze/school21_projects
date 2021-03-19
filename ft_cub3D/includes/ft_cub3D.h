/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:00:31 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 18:31:24 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>

# define IS_SPACE(val) ((val >= 9 && val <= 13) || val == ' ')

# define IS_MAP_CHAR(val) (val == ' ' || val == '0' || val == '1')

# define IS_PLR_CHAR(val) (val == 'W' || val == 'S' || val == 'N' || val == 'E')

# define IS_NOT_TRUE_FORMAT(val) (argv[1][val] != 'b' || argv[1][val - 1] != 'u'\
		|| argv[1][val - 2] != 'c' || argv[1][val - 3] != '.')

typedef struct	s_maze_params {
	long	w_h;
	int		c_f[2];
	int		no_txt;
	int 	we_txt;
	int		ea_txt;
	int		so_txt;
	int		sprite_txt;
}				t_maze_params;

typedef struct	s_plr {
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				t_plr;

typedef struct		s_spr_list {
	int					coords;
	struct s_spr_list	*next;
}					t_spr_list;

typedef struct	s_all {
	char			**map;
	t_maze_params	*maze;
	t_plr			*plr;
	int				*spr;
	int				spr_len;
}				t_all;

typedef struct		s_compose {
	t_all		*result;
	t_list		*map_struct;
	t_spr_list	*spr_struct;
	int			max_x;
	int			max_y;
}					t_compose;

void    ft_putstr(char *str);

t_all	*map_file_parser(int fd);

long	ft_strtol(const char *nptr, char **endptr, int base);

void    exit_with_message(char *str, t_all *t);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void    flood_fill(t_compose *t, int pos_x, int pos_y);

void	map_parser(int fd, t_all *result, char *line);

void    sprite_array_maker(t_compose *t);

void    map_maker(t_compose *t);

void    map_error(char *str, t_compose *t, char *line);

#endif
