/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 08:45:00 by mchau             #+#    #+#             */
/*   Updated: 2020/11/18 13:59:16 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <printf.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	char *line = 0;
	int i = 0;
	int fd = 0;
	if(argc == 2)
		fd= open(argv[1], O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%d : %s\n", i, line);
		free(line);
	}
	printf("%d : %s\n", i, line);
	free(line);
	i = get_next_line(fd, &line);
	printf("%d : %s\n", i, line);
	free(line);
}
