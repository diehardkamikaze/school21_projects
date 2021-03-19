/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 08:37:44 by mchau             #+#    #+#             */
/*   Updated: 2021/03/19 10:40:57 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int					get_next_line(int fd, char **line);

char				*ft_substr(char *s, size_t start, size_t len);

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
	int				len;
}					t_list;

typedef struct		s_o
{
	size_t	line_len;
	t_list	*lst;
	char	*buffer;
	char	*divider;
	long	i;
	char	*tmp;
}					t_o;

t_list				*ft_lstnew(char *content);

int					ft_lstadd_back(t_list **lst, t_list *new);

int					ft_lstclear(t_list **lst);

char				*ft_strchr(const char *s, int c);

#endif
