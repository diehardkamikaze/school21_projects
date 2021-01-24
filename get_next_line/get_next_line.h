/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 08:37:44 by mchau             #+#    #+#             */
/*   Updated: 2020/11/18 17:47:10 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //del that

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#if BUFFER_SIZE < 0
#undef BUFFER_SIZE
#define BUFFER_SIZE = 1
#endif

int					get_next_line(int fd, char **line);

char				*ft_substr(char *s, unsigned int start, size_t len);

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
	int				len;
}					t_list;

t_list				*ft_lstnew(char *content, int len);

void				ft_lstadd_back(t_list **lst, t_list *new);

int					ft_lstclear(t_list **lst);

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

char				*ft_strchr(const char *s, int c);

#endif
