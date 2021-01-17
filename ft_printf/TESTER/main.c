/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:47:51 by mchau             #+#    #+#             */
/*   Updated: 2021/01/17 13:58:14 by mchau            ###   ########.fr       */
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
	/* %tests */
	assert(PRINT_F("test: %.%"));
	assert(PRINT_F("test: %.10%"));
	assert(PRINT_F("test: %.*%", -10));
	assert(PRINT_F("test: %10.%"));
	assert(PRINT_F("test: %*.%", -10));
	assert(PRINT_F("test: %9.10%"));
	assert(PRINT_F("test: %*.10%,", -1));
	assert(PRINT_F("test: %9.*%", -10));
	assert(PRINT_F("test: %*.*%", -8, -7));

	assert(PRINT_F("test: %-.%"));
	assert(PRINT_F("test: %-.10%"));
	assert(PRINT_F("test: %-.*%", -10));
	assert(PRINT_F("test: %-10.%"));
	assert(PRINT_F("test: %-*.%", -10));
	assert(PRINT_F("test: %-9.10%"));
	assert(PRINT_F("test: %-*.10%", -19));
	assert(PRINT_F("test: %-9.*%", -10));
	assert(PRINT_F("test: %-*.*%", -8, -7));

	assert(PRINT_F("test: %0.%"));
	assert(PRINT_F("test: %0.10%"));
	assert(PRINT_F("test: %0.*%", -10));
	assert(PRINT_F("test: %010.%"));
	assert(PRINT_F("test: %0*.%", -10));
	assert(PRINT_F("test: %09.10%"));
	assert(PRINT_F("test: %0*.10%", -19));
	assert(PRINT_F("test: %09.*%", -10));
	assert(PRINT_F("test: %0*.*%", -8, -7));

	assert(PRINT_F("test: %-0.%"));
	assert(PRINT_F("test: %-0.10%"));
	assert(PRINT_F("test: %-0.*%", -10));
	assert(PRINT_F("test: %-010.%"));
	assert(PRINT_F("test: %-0*.%", -10));
	assert(PRINT_F("test: %-09.10%"));
	assert(PRINT_F("test: %-0*.10%", -19));
	assert(PRINT_F("test: %-09.*%", -10));
	assert(PRINT_F("test: %-0*.*%", -8, -7));

	/* end of %% tests  */

	/* %c tests */
	assert(PRINT_F("test: %c", 88));
	assert(PRINT_F("test: %10c", 89));
	assert(PRINT_F("test: %*c", -89));

	assert(PRINT_F("test: -%c", 88));
	assert(PRINT_F("test: %-10c", 89));
	assert(PRINT_F("test: %-*c", -89));

	/* end of %c tests */

	/* %s tests */
	assert(PRINT_F("test: %s", "almaz"));
	assert(PRINT_F("test: %.s", "almazyan"));
	assert(PRINT_F("test: %.*s", 0, "toptoptoptop"));
	assert(PRINT_F("test: %.*s", -8, "almaz"));
	assert(PRINT_F("test: %.10s", "almaz"));
	assert(PRINT_F("test: %.4s", "almaz"));
	assert(PRINT_F("test: %2s", "almaz"));
	assert(PRINT_F("test: %12s", "almaz"));
	assert(PRINT_F("test: %2.s", "almaz"));
	assert(PRINT_F("test: %*.s", 2, "almaz"));
	assert(PRINT_F("test: %*.s", 16, "almaz"));
	assert(PRINT_F("test: %*.*s", -8, -8, "almaz"));
	assert(PRINT_F("test: %*.*s", 17, -8, "almaz"));
	assert(PRINT_F("test: %*.*s", 2, -8, "almaz"));
	assert(PRINT_F("test: %*.10s", -10,  "almaz"));
	assert(PRINT_F("test: %*.10s", 3, "almaz"));
	assert(PRINT_F("test: %*.10s", 8, "almaz"));
	assert(PRINT_F("test: %12.*s", 3, "almaz"));
	assert(PRINT_F("test: %99.*s", 3,"almaz"));

	assert(PRINT_F("test: %-s", "almaz"));
	assert(PRINT_F("test: %-.s", "almazyan"));
	assert(PRINT_F("test: %-.*s", 0, "toptoptoptop"));
	assert(PRINT_F("test: %-.*s", -8, "almaz"));
	assert(PRINT_F("test: %-.10s", "almaz"));
	assert(PRINT_F("test: %-.4s", "almaz"));
	assert(PRINT_F("test: %-2s", "almaz"));
	assert(PRINT_F("test: %-12s", "almaz"));
	assert(PRINT_F("test: %-2.s", "almaz"));
	assert(PRINT_F("test: %-*.s", 2, "almaz"));
	assert(PRINT_F("test: %-*.s", 16, "almaz"));
	assert(PRINT_F("test: %-*.*s", -8, -8, "almaz"));
	assert(PRINT_F("test: %-*.*s", 17, -8, "almaz"));
	assert(PRINT_F("test: %-*.*s", 2, -8, "almaz"));
	assert(PRINT_F("test: %--*.10s", -10,  "almaz"));
	assert(PRINT_F("test: %-*.10s", 3, "almaz"));
	assert(PRINT_F("test: %-*.10s", 8, "almaz"));
	assert(PRINT_F("test: %-12.*s", 3, "almaz"));
	assert(PRINT_F("test: %-99.*s", 3,"almaz"));
	/* end of %s tests */

}

int		main()
{
	g_special_random_fd = open("system_printf_output", O_WRONLY | O_TRUNC);
	if (g_special_random_fd != -1)
		start_tests();
	return (0);
}
