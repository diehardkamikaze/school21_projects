# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/02 17:49:28 by mchau             #+#    #+#              #
#    Updated: 2021/01/14 13:11:09 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SOURCES = *.c
OBJECTS = *.o

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c  $(SOURCES)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

re: clean all

.PHONY: all clean fclean re
