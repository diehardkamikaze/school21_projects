/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:52:52 by mchau             #+#    #+#             */
/*   Updated: 2021/05/23 13:04:57 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <term.h>

int		main(void)
{
	char some_str[2000];
	int l;
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	do
	{
		l = read(0, some_str, 100);
		write(1, some_str, l);
	}
	while (strcmp(some_str, "\n"));
	write(1, "\n", 1);
	return (0);
}
