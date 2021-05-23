/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:52:52 by mchau             #+#    #+#             */
/*   Updated: 2021/05/23 12:40:06 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int		main(void)
{
	char some_str[2000];
	int l;
	l = read(0, some_str, 1000);
	write(1, some_str, l);
	return (0);
}
