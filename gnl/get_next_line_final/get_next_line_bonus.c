/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:25:04 by mchau             #+#    #+#             */
/*   Updated: 2020/11/25 09:16:49 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

int		make_result_array(char **line, t_list **lst, size_t line_len)
{
	char	*result;
	int		i;
	char	*content;
	t_list	*tmp;

	result = 0;
	i = 0;
	if (!(result = malloc(line_len + 1)))
		return (0);
	result[line_len] = 0;
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
	return (1);
}

int		selected_free(char *buffer, char *remainder, t_list *lst)
{
	free(buffer);
	free(remainder);
	if (lst)
		ft_lstclear(&lst);
	return (-1);
}

int		one_iter(t_o *o, char **remainder, char **line)
{
	if (o->i < 0 || (o->buffer[o->i] = 0))
		return (selected_free(o->buffer, *remainder, o->lst));
	if ((o->divider = ft_strchr(o->buffer, '\n')))
	{
		*(o->divider) = 0;
		if ((o->divider - o->buffer) && (o->line_len += o->divider - o->buffer))
			if (!(o->tmp = ft_substr(o->buffer, 0, o->divider - o->buffer)) ||
				ft_lstadd_back(&(o->lst), ft_lstnew(o->tmp)) || (o->tmp = 0))
				return (selected_free(o->buffer, *remainder, o->lst));
		if ((o->i > (long)(o->divider - o->buffer + 1)) && !(*remainder =
					ft_substr(o->buffer, o->divider - o->buffer + 1,
						o->i - (o->divider - o->buffer + 1))))
			return (selected_free(o->buffer, *remainder, o->lst));
		if (!(make_result_array(line, &(o->lst), o->line_len)))
			return (selected_free(o->buffer, *remainder, o->lst));
		selected_free(o->buffer, 0, o->lst);
		return (1);
	}
	o->line_len += o->i;
	ft_lstadd_back(&(o->lst), ft_lstnew(o->buffer));
	o->i = 0;
	if (!(o->buffer = malloc(BUFFER_SIZE + 1)))
		return (selected_free(o->buffer, 0, o->lst));
	return (-2);
}

int		get_next_line(int fd, char **line)
{
	t_o			o;
	int			time;
	static char	*remainder[10241];

	o.i = 0;
	o.line_len = 0;
	o.lst = 0;
	o.divider = 0;
	o.buffer = 0;
	if (remainder[fd] && (o.buffer = remainder[fd]))
	{
		remainder[fd] = 0;
		o.i = ft_strlen(o.buffer);
	}
	else
		o.buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || line == 0 || BUFFER_SIZE < 1 || !(o.buffer))
		return (selected_free(o.buffer, remainder[fd], o.lst));
	while (o.i || (o.i = read(fd, o.buffer, BUFFER_SIZE)))
		if ((time = one_iter(&o, &(remainder[fd]), line)) != -2)
			return (time);
	if (!(make_result_array(line, &o.lst, o.line_len)))
		return (selected_free(o.buffer, remainder[fd], o.lst));
	selected_free(o.buffer, remainder[fd], o.lst);
	return (0);
}
