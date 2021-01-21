# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:26:45 by mchau             #+#    #+#              #
#    Updated: 2021/01/21 17:36:52 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################

# VARIABLES:

################################################################################

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SOURCES = p_handler.c percent_handler.c c_handler.c ft_printf.c ft_puts.c\
		  ft_strtol.c s_handler.c ft_parser.c ft_putnbr.c ft_strchr.c\
		  ft_utf_codings.c

# DIRS

OBJ_DIR = objs
SRC_DIR = srcs
INC_DIR = includes

# PREPROCESS

OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SOURCES)))


###############################################################################

# TARGETS:

################################################################################

all: $(NAME)

#test obj_dir when obj changed -> get error mkdir?
$(NAME): $(OBJ_DIR) $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/ft_printf.h
	gcc $(FLAGS) -c $< -o $@ -I$(INC_DIR)

bonus: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	make && gcc -Wall -Wextra -Werror -I.\
		main.c -L. -lftprintf  && ./a.out

.PHONY: all clean fclean re test
