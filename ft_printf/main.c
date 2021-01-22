/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 12:54:02 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

int main(void)
{
	setlocale(LC_ALL, "");
	printf("%lfi", 44./0);
	return (0);
}
