/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 08:58:42 by mchau             #+#    #+#             */
/*   Updated: 2020/12/11 17:06:31 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ft_printf.h"

int main()
{
	char *test = 0;
	ft_printf("---char test---\n");
	ft_printf("some text %c with some enother text", 120);
	char c = 99;
	ft_printf("some text %c %c %c %c %c %c with some another texts\n%c", c, c, c, c, c, c, 4.67);
	printf("it's a %s %c.2 %s", test, 'v', "HAHAHAHAHAHAHA");
	ft_printf("it's a %s %c.2 %s", test, 'v', "HAHAHAHAHAHAHA");
	//	printf("some text %c with some enother text\n", 120);
	return (0);
}

