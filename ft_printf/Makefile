# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 17:26:45 by mchau             #+#    #+#              #
#    Updated: 2021/01/18 18:46:29 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################

# VARIABLES:

################################################################################

NAME = libftprintf.a
HEADER_DIR = .
FLAGS = -Wall -Wextra -Werror
SOURCES = ft_printf.c ft_printf_parser_handlers.c ft_printf_spec_handlers.c\
		ft_printf_spec_handlers2.c ft_putnbr.c ft_puts.c\
		ft_strchr.c ft_strtol.c

OBJ = $(patsubst %.c, %.o, $(SOURCES))
################################################################################

# TARGETS:

################################################################################

all: $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o : %.c ft_printf.h
	gcc $(FLAGS) -c $< -I$(HEADER_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
