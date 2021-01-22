/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 14:24:16 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

void print_bits(unsigned long long a, int nbits)
{
	 unsigned long long b = a;
	  	for (int i = 0; i < nbits; ++i)
 	{
 		printf("%d", (int)(b & 1)); /* b % 2 */
 		b >>= 1; /* b /= 2 */
 	}
}

int main(void)
{
	setlocale(LC_ALL, "");
	//print_bits(0.125, 64);

	printf("| %d\n", ft_printf("%.lu", 0));
	printf("| %d", printf("%.lu", 0));
	return (0);
}
