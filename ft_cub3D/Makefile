# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 14:12:05 by mchau             #+#    #+#              #
#    Updated: 2021/03/11 15:04:45 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################
# VARIABLES:
#################################################

NAME = cub3D
FLAGS = -Wall -Wextra -Werror
SOURCES = cub3D.c gnl/get_next_line.c gnl/get_next_line_utils.c

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

$(NAME): $(OBJ_DIR) $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -I$(INC_DIR) -o $@
# gcc main.c -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit -I.

$(OBJ_DIR):
	mkdir $@

%.o:
	echo $@

$(OBJ_DIR)/%.o: %.с $(INC_DIR)/*.h
	gcc -$(FLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:  all clean fclean re
