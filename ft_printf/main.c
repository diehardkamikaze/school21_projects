/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/01/20 17:05:43 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

int main(void)
{
	setlocale(LC_ALL, "");

	//wchar_t *x = 0;
//	double g = 0.52;
	printf("|%d\n", printf("%+20.*lf", -5,  DBL_MAX * 2));
	return (0);
}
