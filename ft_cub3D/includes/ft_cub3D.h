/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:00:31 by mchau             #+#    #+#             */
/*   Updated: 2021/03/23 17:09:07 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <errno.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include "../minilibx_opengl/mlx.h"
#include "../minilibx_opengl/mlx.h"

# define SPR_TXT 0

# define NO_TXT	1

# define WE_TXT 2

# define SO_TXT 3

# define EA_TXT 4

# define PI 3.14159265

# define MOVE_SPEED 0.1f

# define ROT_SPEED 0.08f

# define IS_SPACE(val) ((val >= 9 && val <= 13) || val == ' ')

# define IS_MAP_CHAR(val) (val == ' ' || val == '0' || val == '1')

# define IS_PLR_CHAR(val) (val == 'W' || val == 'S' || val == 'N' || val == 'E')

# define IS_NOT_TRUE_FORMAT(val) (argv[1][val] != 'b' || argv[1][val - 1] \
		!= 'u' || argv[1][val - 2] != 'c' || argv[1][val - 3] != '.')

typedef struct		s_key_state {
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_arrow_left;
	int	key_arrow_right;
}					t_key_state;

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	unsigned int		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				  t_win;

typedef struct	s_maze_params {
	long	w_h;
	int		c_f[2];
	char	*textures[5];
}				t_maze_params;

typedef struct	s_plr {
	float		x;
	float		y;
	float		dirX;
	float		dirY;
	float		planeX;
	float		planeY;
}				t_plr;

typedef struct		s_spr_list {
	int					coords;
	struct s_spr_list	*next;
}					t_spr_list;

typedef struct	s_all {
	t_win			*game;
	char			**map;
	t_maze_params	*maze;
	t_plr			*plr;
	int				*spr;
	int				spr_len;
	t_key_state		pressed;
	void			*txt_img[5];
	int				txt_size[2];
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

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_bzero(void *s, size_t n);

char	*ft_strdup(const char *);

void    flood_fill(t_compose *t, int pos_x, int pos_y);

void	map_parser(int fd, t_all *result, char *line);

void    sprite_array_maker(t_compose *t);

void    free_wrapper(t_all *t);

void    exit_with_message(char *str, t_all *t);

void    map_maker(t_compose *t);

void    map_error(char *str, t_compose *t, char *line);

void    go_game_logic(t_all *t);

int		key_press_handler(int keycode, void *param);

int		key_release_handler(int keycode, void *param);

int		exit_handler(void *param);

void    fill_image_by_map(t_all *t);

int		key_state_checker(void *param);

int		handle_moving_ws(int dir, t_all *t);

int		handle_moving_ad(float dir, t_all *t);

int		handle_rotating(int dir, t_all *t);

void    bmp_maker(t_all *t);

#endif
