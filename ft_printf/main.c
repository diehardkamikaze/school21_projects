/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:25 by mchau             #+#    #+#             */
/*   Updated: 2021/01/17 12:01:18 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int main(void)
{
	printf("|%d\n", ft_printf("test: %0%"));
	printf("|%d\n", ft_printf("test: %0-%"));
	printf("|%d\n", ft_printf("test: %0%"));
	printf("|%d\n", ft_printf("test: %0%"));
	printf("|%d\n", ft_printf("test: %0%"));
	printf("|%d\n", ft_printf("test: %0%"));
	// printf("%d\n", ft_printf("%*.*s\n",-10, 0, "almaz"));
	return (0);
}
