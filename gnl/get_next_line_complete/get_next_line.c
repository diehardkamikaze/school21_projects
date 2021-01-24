/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:18:58 by mchau             #+#    #+#             */
/*   Updated: 2020/11/24 16:25:42 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!(result = malloc(line_len + 1)) || (result[line_len] = 0))
		return (ft_lstclear(lst));
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

int	selected_free(char *buffer, char *remainder, t_list *lst)
{
	free(buffer);
	free(remainder);
	if (lst)
		ft_lstclear(&lst);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	size_t		line_len;
	t_list		*lst;
	static char	*remainder;
	char		*buffer;
	char		*divider;
	long		i;

	//pod proverky ne?
	if (!(i = 0) && !(line_len = 0) && !(lst = 0) && !(divider = 0) &&
			!(buffer = 0) && remainder)
	{
		i = ft_strlen(remainder);
		buffer = remainder;
		remainder = 0;
	}
	else
		buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || line == 0 ||  BUFFER_SIZE < 1 || !buffer)
		return (-1);
	while (i || (i = read(fd, buffer, BUFFER_SIZE)))
	{
		if (i < 0)
			return (-1);
		buffer[i] = 0;
		if ((divider = ft_strchr(buffer, '\n')) && !(*divider = 0))
		{
			if (divider - buffer)
			{
				line_len += (divider - buffer);
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(buffer, 0, divider - buffer)));
				//proverki na 0 malloc
			}
		//	printf("%ld\n", i - (divider - buffer + 1));
			if ((i > (long)(divider - buffer + 1)))
				remainder = ft_substr(buffer,
						divider - buffer + 1, i - (divider - buffer + 1));
			//	return (selected_free(buffer, remainder, lst));//peredelat otdelno 1 usl
			if (!(make_result_array(line, &lst, line_len)))
					return (selected_free(buffer, remainder, lst));
		//	printf("remainder : %s\n", remainder);
		//	printf("line : %s\n", *line);
		//	printf("------\n");;
			selected_free(buffer, 0, lst);
			return (1);
		}
		line_len += i;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(buffer, 0, i))); // prover malloc
		i = 0;
		if (!(buffer = 0) && !(buffer = malloc(BUFFER_SIZE + 1)))
			return (selected_free(buffer, 0, lst));

	}
	if (!(make_result_array(line, &lst, line_len)))
		return (selected_free(buffer, remainder, lst));
	selected_free(remainder, buffer, lst);
	return (0);
}
