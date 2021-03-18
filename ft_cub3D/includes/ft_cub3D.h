/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:00:31 by mchau             #+#    #+#             */
/*   Updated: 2021/03/18 13:44:39 by mchau            ###   ########.fr       */
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

typedef struct	s_maze_params {
	int		w_h[2];
	int		c_f[2];
	char	*no_txt;
	char	*we_txt;
	char	*ea_txt;
	char	*so_txt;
	char	*sprite_txt;
}				t_maze_params;

typedef struct	s_all {
	char			**map;
	t_maze_params	*maze;
}				t_all;

void    ft_putstr(char *str);

t_all	*map_parser(int fd);

long	ft_strtol(const char *nptr, char **endptr, int base);

void    exit_with_message(char *str, t_all *t);

#endif
