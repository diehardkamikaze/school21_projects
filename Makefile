# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/02 17:49:28 by mchau             #+#    #+#              #
#    Updated: 2020/12/02 18:02:14 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SOURCES = *.c


all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -fsanitize=address -g $(SOURCES)

clean:
	rm -rf a.out

re: clean all

.PHONY: all clean fclean re
