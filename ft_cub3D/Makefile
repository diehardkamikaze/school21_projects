# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 14:12:05 by mchau             #+#    #+#              #
#    Updated: 2021/04/22 18:30:20 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################
# VARIABLES:
#################################################

NAME = cub3D
FLAGS = -Wall -Wextra -Werror
SOURCES = cub_starter.c bmp_maker.c map_file_parser.c array_makers.c\
		  map_parser.c sort.c world_draws.c flood_fill.c event_handlers.c\
		  move_handlers.c inits.c errors.c go_game_logic.c sprite_draws.c\
		  utils/ft_strncmp.c utils/ft_bzero.c utils/ft_cub3d_utils_print.c\
		  utils/ft_strtol.c utils/ft_strdup.c gnl/get_next_line.c\
		  gnl/get_next_line_utils.c

################################################
# DIRS:
################################################

INC_DIR = includes
OBJ_DIR = objs

################################################
# PREPROCESS:
################################################

OBJECTS = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SOURCES)))

###############################################
# TARGETS:
###############################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS) includes/ft_cub3d.h includes/get_next_line.h
	$(MAKE) -C minilibx_opengl
	gcc $(FLAGS) $(OBJECTS) -I$(INC_DIR) -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -o $@

$(OBJ_DIR):
	mkdir $@
	mkdir $@/gnl
	mkdir $@/utils

$(OBJ_DIR)/%.o: %.c
	gcc $(FLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C minilibx_opengl

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:  all clean fclean re
