# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 12:09:47 by mchau             #+#    #+#              #
#    Updated: 2020/11/12 05:51:33 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
WARNINGFLAGS = -Wall -Wextra -Werror
SOURCES =  ft_bzero.c ft_putendl_fd.c ft_strlcpy.c\
			ft_tolower.c ft_calloc.c ft_memccpy.c\
			ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_isalnum.c\
			ft_memchr.c	ft_putstr_fd.c ft_strmapi.c\
			ft_isalpha.c ft_memcmp.c ft_split.c\
			ft_strncmp.c ft_isascii.c ft_memcpy.c\
			ft_strchr.c	ft_strnstr.c ft_isdigit.c\
			ft_memmove.c ft_strdup.c ft_strrchr.c\
			ft_isprint.c ft_memset.c ft_strjoin.c ft_strtrim.c\
			ft_atoi.c ft_itoa.c	ft_putchar_fd.c	ft_strlcat.c ft_substr.c
GARBAGE = $(SOURCES:.c=.o)
BONUSES = ft_lstadd_back.c ft_lstclear.c ft_lstiter.c\
		  ft_lstmap.c ft_lstsize.c ft_lstadd_front.c\
		  ft_lstdelone.c ft_lstlast.c ft_lstnew.c

GARBAGE_BONUS = $(BONUSES:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	gcc $(WARNINGFLAGS) -c $< -o $@

$(NAME): $(GARBAGE)
	ar rc $(NAME) $(GARBAGE)
	ranlib $(NAME)

bonus: $(GARBAGE_BONUS) $(GARBAGE)
	ar rc $(NAME) $(GARBAGE) $(GARBAGE_BONUS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(GARBAGE) $(GARBAGE_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
