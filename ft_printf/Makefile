# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/02 17:49:28 by mchau             #+#    #+#              #
#    Updated: 2021/01/15 19:31:58 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SOURCES = *.c ./service/prepare*.c
OBJECTS = *.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SOURCES) -I.
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f  $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
