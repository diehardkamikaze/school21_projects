/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:52:52 by mchau             #+#    #+#             */
/*   Updated: 2021/04/16 17:22:00 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void	before_exit(int sig)
{
	printf("now i going to sleep");
	exit(1);
}

int		main(void)
{
	int c;
	struct sigaction action;

	action.sa_handler = before_exit;
	sigemptyset(&(action.sa_mask));
	action.sa_flags = 0;
	sigaction(SIGINT, &action, 0);
	while((c=fgetc(stdin)) !=EOF) {
		printf("%c", c);
	}
	/*	int pid;
	int fd[2];

	pipe(fd); //защити [ отсюда считываем, cюда записываем ]
	pid = fork(); // защити
	write(fd[1], "1", 1);
	if (!pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		execl("./test", 0); //защити
	}
	close(fd[0]);
	dup2(fd[1], 1);
	//while (1)
		write(fd[1], "1", 1); //раньше пишем в буфер, чем запускается дочерний процесс, но разве это не кусок памяти?
*/
	return (0);
}
