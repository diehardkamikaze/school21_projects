# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 14:12:05 by mchau             #+#    #+#              #
#    Updated: 2021/03/28 18:15:41 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################
# VARIABLES:
#################################################

NAME = cub3D
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SOURCES = cub_starter.c bmp_maker.c map_file_parser.c map_makers.c map_parser.c\
		  flood_fill.c event_handlers.c move_handlers.c map_render.c \
		  go_game_logic.c utils/ft_strncmp.c utils/ft_bzero.c \
		  utils/ft_cub3D_utils_print.c utils/ft_strtol.c utils/ft_strdup.c \
		  gnl/get_next_line.c gnl/get_next_line_utils.c

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

makelib:
	$(MAKE) -C minilibx_opengl

$(NAME): makelib $(OBJ_DIR) $(OBJECTS)
	#gcc $(FLAGS) $(OBJECTS) -I$(INC_DIR) -o $@
	gcc $(FLAGS) $(OBJECTS) -I$(INC_DIR) -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -o $@

$(OBJ_DIR):
	mkdir $@
	mkdir $@/gnl
	mkdir $@/utils

$(OBJ_DIR)/%.o: %.c
	gcc $(FLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:  all clean fclean re
