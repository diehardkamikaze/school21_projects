/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:47:51 by mchau             #+#    #+#             */
/*   Updated: 2021/01/14 13:17:11 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <assert.h>
#include "ft_printf.h"

int g_special_random_fd = 0;

int	PRINT_F(char *format, ...)
{
	int system_res;
	int user_res;

	va_list ptr;
	va_list ptr_copy;
	va_copy(ptr_copy, ptr);
	va_start(ptr, format);
	va_start(ptr_copy, format);

	system_res = vdprintf(g_special_random_fd, format, ptr);
	user_res = ft_vprintf(format, ptr_copy);
	va_end(ptr);
	va_end(ptr_copy);
	return (system_res == user_res);
}

void	start_tests()
{
	assert(PRINT_F("%c\n", 88));
}

int		main()
{
	g_special_random_fd = open("system_printf_output", O_WRONLY | O_TRUNC);
	if(g_special_random_fd != -1)
	{
		start_tests();
	}
	return (0);
}
