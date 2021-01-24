/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:25:24 by mchau             #+#    #+#             */
/*   Updated: 2020/11/25 08:49:29 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
