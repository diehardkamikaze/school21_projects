/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 11:43:31 by mchau             #+#    #+#             */
/*   Updated: 2021/06/19 11:52:28 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int catch_signal(int sig, void (*handler)(int)) {
	struct sigaction action;
	action.sa_handler = handler;
	if (sigemptyset(&action.sa_mask) == -1)
		return (-1);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);
}

void mainhandler(int sig) {
	printf("ALLAHYU AKBAR!");
	exit(1);
}

int main(void) {
	if (catch_signal(SIGINT, mainhandler) == -1) {
		printf("hueta slu4aetsya");
		return (1);
	}
	while (1) {
		printf("i believe, i can fly");
	}
	return 0;
}
