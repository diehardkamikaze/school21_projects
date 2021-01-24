/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:42:02 by mchau             #+#    #+#             */
/*   Updated: 2020/11/24 13:43:09 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	rebuff(char **buf, unsigned int from)
{
	char *tmp;

	tmp = ft_substr(*buf, from, BUFFER_SIZE);
	free(*buf);
	*buf = tmp;
}

int		get_size(t_list *lst)
{
	int	res;

	res = 0;
	while(lst)
	{
		res = res + lst->len;
		lst = lst->next;
	}
	return (res);
}

int		make_result_array(char **line, t_list **lst, int size)
{
	char	*result;
	int		i;
	char	*content;
	t_list	*tmp;

	result = 0;
	i = 0;
	result = (char *)malloc(size + 1);
	if (!result || !lst)
		return (ft_lstclear(lst));
	result[size] = 0;
	while (*lst)
	{
		content = (*lst)->content;
		while (*content)
		{
			result[i++] = *(content);
			content++;
		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*line = result;
	result = 0;
	return (1);
}

int special_i(int fd, char **line, char **buf_spec)
{
	char	*buf;
	int		i;

	i = 0;
	buf = *buf_spec;
	if (fd >=0 && line != 0 && BUFFER_SIZE >= 0 && !buf && (buf = (char *)malloc(BUFFER_SIZE + 1)))
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
	}
	if (!buf)
		return (-1);
	if(i < 0)
	{
		free(buf);
		return (-1);
	}
	*buf_spec = buf;
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char *buf;
	int			i;
	char		*until;
	t_list		*lst;

	i = 0;
	while (buf || (i = (special_i(fd, line, &buf)) > 0))
	{
		if ((until = ft_strchr(buf, '\n')))
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(buf, 0, until - buf), until - buf));
			// add to list from start to until;
			rebuff(&buf, until - buf);
				//free buff until until
			make_result_array(line, &lst, get_size(lst));
				//make line
			return (1);
				//result 1; // check (i < BUFF_SIZE && until - buf == 0) count to return 0?
		}
		//add to list from start to unti;
		//free buff until until
		int g = 0;
		while(buf[g])
			g++;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(buf, 0, g), g));
		free(buf);
		buf = 0;;
		//check  i < BUFF_SIZE count to return 0? make line?
	}
	if (i == -1)
		return (-1);
	make_result_array(line, &lst, get_size(lst));
	return (0);
}
