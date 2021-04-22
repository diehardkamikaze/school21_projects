/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:49:27 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:49:30 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <errno.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include "../minilibx_opengl/mlx.h"
# include "../minilibx_opengl/mlx.h"

# define SPR_TXT 0

# define NO_TXT	1

# define WE_TXT 2

# define SO_TXT 3

# define EA_TXT 4

# define PI 3.14159265

# define MOVE_SPEED 0.08f

# define ROT_SPEED 0.06f

# define IS_SPACE(val) ((val >= 9 && val <= 13) || val == ' ')

# define IS_ALLOWED_CHAR(v) (v == ' ' || v == '0' || v == '1' || v == '2')

# define IS_PLR_CHAR(val) (val == 'W' || val == 'S' || val == 'N' || val == 'E')

typedef struct	s_key_state {
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_arrow_left;
	int	key_arrow_right;
	int key_arrow_top;
	int key_arrow_bottom;
}				t_key_state;

typedef struct	s_win
{
	void				*mlx;
	void				*win;
	void				*img;
	unsigned int		*addr;
	int					line_l;
	int					bpp;
	int					en;
}				t_win;

typedef struct	s_maze_params {
	long	w_h[2];
	int		c_f[2];
	char	*textures[5];
}				t_maze_params;

typedef struct	s_plr {
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		vertical;
}				t_plr;

typedef struct	s_spr_list {
	int					coords;
	struct s_spr_list	*next;
}				t_spr_list;

typedef struct	s_all {
	t_win			game;
	char			**map;
	t_maze_params	*maze;
	t_plr			*plr;
	int				*spr;
	int				spr_len;
	t_key_state		pressed;
	void			*txt_img[5];
}				t_all;

typedef struct	s_compose {
	t_all		*result;
	t_list		*map_struct;
	t_spr_list	*spr_struct;
	int			max_x;
	int			max_y;
}				t_compose;

typedef struct	s_draw {
	double	raydir_x;
	double	raydir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	int		draw_start;
	int		draw_end;
	int		side;
	int		line_height;
	double	wall_dist;
	double	vert_pos;
	int		width;
	int		height;
	int		x;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
}				t_draw;

typedef struct	s_draw_spr {
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				spr_screen_x;
	int				move_screen;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				tex_width;
	int				tex_height;
	unsigned int	*texture;
}				t_draw_spr;

typedef struct	s_draw_texture {
	double			wall_x;
	int				tex_width;
	int				tex_height;
	unsigned int	*texture;
	int				tex_x;
	int				tex_y;
	double			scale;
	double			tex_start;
}				t_draw_texture;

typedef struct	s_tex_coords {
	int	tex_x;
	int	tex_y;
	int	line;
}				t_tex_coords;

void			ft_putstr(char *str);

t_all			*map_file_parser(int fd);

long			ft_strtol(const char *nptr, char **endptr, int base);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

void			ft_bzero(void *s, size_t n);

char			*ft_strdup(const char *s1);

void			flood_fill(t_compose *t, int pos_x, int pos_y);

void			map_parser(int fd, t_all *result, char *line);

void			sprite_array_maker(t_compose *t);

void			free_wrapper(t_all *t);

void			exit_with_message(char *str, t_all *t);

void			map_array_maker(t_compose *t);

void			go_game_logic(t_all *t);

int				key_handler(int keycode, void *param);

int				exit_handler(void *param);

int				fill_image_by_game(t_all *t);

int				key_state_checker(void *param);

int				handle_moving_ws(int dir, t_all *t);

int				handle_moving_ad(double dir, t_all *t);

int				handle_rotating(int dir, t_all *t);

void			bmp_maker(t_all *t);

void			init_game (t_all *t);

int				render_map(t_all *t);

int				handle_vertical_rotation(int dir, t_all *t);

unsigned int	*get_world_side_txt(t_all *t, t_draw *d, int *wi, int *hi);

void			maze_error(char *str, t_all *t, char *line, int fd);

void			exit_with_message(char *str, t_all *t);

void			map_error(char *str, t_compose *t, char *line, int fd);

void			map_malloc_error(int i, t_compose *t);

t_all			*initialize_master_struct(int fd);

void			init_game (t_all *t);

void			init_map_vars(t_compose *t, t_all *result);

void			init_draw_vars(t_draw *d, t_all *t);

void			draw_ceil(t_draw *d, t_all *t);

void			draw_floor(t_draw *d, t_all *t);

void			draw_texture(t_draw *d, t_all *t);

void			sort_all_sprites(int *sprite_order,\
		double *sprite_distance, int len);

void			draw_objects(t_all *t, t_draw *d, double *z_buffer);

void			draw_sprite(t_all *t, t_draw *d, int i, double *z_buffer);

#endif
