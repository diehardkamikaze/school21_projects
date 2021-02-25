/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:47:51 by mchau             #+#    #+#             */
/*   Updated: 2021/02/20 14:22:43 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <assert.h>
#include <locale.h>
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
	vdprintf(g_special_random_fd, "\n", ptr);
	user_res = ft_vprintf(format, ptr_copy);
	va_end(ptr);
	va_end(ptr_copy);
	vdprintf(1, "\n", ptr);
	return (system_res == user_res);
}
void	start_tests()
{
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
	assert(PRINT_F("test: %lc", L'b'));
	assert(PRINT_F("test: %lc", L'ݿ'));
	assert(PRINT_F("test: %lc", L'൫'));
	assert(PRINT_F("test: %lc", L'🐳'));


	assert(PRINT_F("test: %5c", 88));
	assert(PRINT_F("test: %6lc", L'b'));
	assert(PRINT_F("test: %7lc", L'ݿ'));
	assert(PRINT_F("test: %8lc", L'൫'));
	assert(PRINT_F("test: %9lc", L'🐰'));

	assert(PRINT_F("test: %*c", -3, 88));
	assert(PRINT_F("test: %*lc", -3, L'b'));
	assert(PRINT_F("test: %*lc", -2, L'ݿ'));
	assert(PRINT_F("test: %*lc", -3, L'൫'));
	assert(PRINT_F("test: %*lc", -4, L'🐸'));

	assert(PRINT_F("test: %-c", 88));
	assert(PRINT_F("test: %-lc", L'b'));
	assert(PRINT_F("test: %-lc", L'ݿ'));
	assert(PRINT_F("test: %-lc", L'൫'));
	assert(PRINT_F("test: %-lc", L'🐌'));

	assert(PRINT_F("test: %-5c", 88));
	assert(PRINT_F("test: %-6lc", L'b'));
	assert(PRINT_F("test: %-7lc", L'ݿ'));
	assert(PRINT_F("test: %-8lc", L'൫'));
	assert(PRINT_F("test: %-9lc", L'🐁'));

	assert(PRINT_F("test: %-c", 88));
	assert(PRINT_F("test: %-lc", L'b'));
	assert(PRINT_F("test: %-lc", L'ݿ'));
	assert(PRINT_F("test: %-lc", L'൫'));
	assert(PRINT_F("test: %-lc", L'💩'));
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

	assert(PRINT_F("test: %s", (void *)0));
	assert(PRINT_F("test: %.s", (void *)0));
	assert(PRINT_F("test: %.*s", 0, (void *)0));
	assert(PRINT_F("test: %.*s", -8, (void *)0));
	assert(PRINT_F("test: %.10s", (void *)0));
	assert(PRINT_F("test: %.4s", (void *)0));
	assert(PRINT_F("test: %2s", (void *)0));
	assert(PRINT_F("test: %12s", (void *)0));
	assert(PRINT_F("test: %2.s", (void *)0));
	assert(PRINT_F("test: %*.s", 2, (void *)0));
	assert(PRINT_F("test: %*.s", 16, (void *)0));
	assert(PRINT_F("test: %*.*s", -8, -8, (void *)0));
	assert(PRINT_F("test: %*.*s", 17, -8, (void *)0));
	assert(PRINT_F("test: %*.*s", 2, -8, (void *)0));
	assert(PRINT_F("test: %*.10s", -10, (void *)0));
	assert(PRINT_F("test: %*.10s", 3, (void *)0));
	assert(PRINT_F("test: %*.10s", 8, (void *)0));
	assert(PRINT_F("test: %12.*s", 3, (void *)0));
	assert(PRINT_F("test: %99.*s", 3,(void *)0));

	assert(PRINT_F("test: %-s", (void *)0));
	assert(PRINT_F("test: %-.s", "almazyan"));
	assert(PRINT_F("test: %-.*s", 0, "toptoptoptop"));
	assert(PRINT_F("test: %-.*s", -8, (void *)0));
	assert(PRINT_F("test: %-.10s", (void *)0));
	assert(PRINT_F("test: %-.4s", (void *)0));
	assert(PRINT_F("test: %-2s", (void *)0));
	assert(PRINT_F("test: %-12s", (void *)0));
	assert(PRINT_F("test: %-2.s", (void *)0));
	assert(PRINT_F("test: %-*.s", 2, (void *)0));
	assert(PRINT_F("test: %-*.s", 16, (void *)0));
	assert(PRINT_F("test: %-*.*s", -8, -8, (void *)0));
	assert(PRINT_F("test: %-*.*s", 17, -8, (void *)0));
	assert(PRINT_F("test: %-*.*s", 2, -8, (void *)0));
	assert(PRINT_F("test: %--*.10s", -10,  (void *)0));
	assert(PRINT_F("test: %-*.10s", 3, (void *)0));
	assert(PRINT_F("test: %-*.10s", 8, (void *)0));
	assert(PRINT_F("test: %-12.*s", 3, (void *)0));
	assert(PRINT_F("test: %-99.*s", 3,(void *)0));

	assert(PRINT_F("test: %ls", L"༻ krĬshnaĬts༺  💗 🐄 and 💩" ));
	assert(PRINT_F("test: %ls", (int *)0));
	assert(PRINT_F("test: %.ls", L"༻ krĬshnaĬts༺  💗 🐄 and 💩" ));
	assert(PRINT_F("test: %.ls", (int *)0));
	assert(PRINT_F("test: %.*ls", -10, L"༻ krĬshnaĬts༺  💗 🐄 and 💩" ));
	assert(PRINT_F("test: %.*ls", -10, (int *)0));
	assert(PRINT_F("test: %.100ls", L"༻ krĬshnaĬts༺  💗 🐄 and 💩" ));
	assert(PRINT_F("test: %.100ls", (int *)0));
	assert(PRINT_F("test: %.2ls", L"༻ krĬshnaĬts༺  💗 🐄 and 💩" ));
	assert(PRINT_F("test: %.2ls", (int *)0));
	assert(PRINT_F("test: %.1ls", L"💗💩" ));
	assert(PRINT_F("test: %.5ls", L"💗💩" ));
	assert(PRINT_F("test: %.8ls", L"💗💩" ));

	assert(PRINT_F("test: %10ls", L"💗💩" ));
	assert(PRINT_F("test: %10ls", (int *)0));
	assert(PRINT_F("test: %2ls", L"💗💩" ));
	assert(PRINT_F("test: %2ls", (int *)0));
	assert(PRINT_F("test: %*ls", -23, L"💗💩" ));
	assert(PRINT_F("test: %*ls", -16, (int *)0));

	assert(PRINT_F("test: %-ls", L"💗💩" ));
	assert(PRINT_F("test: %-ls", (int *)0));

	assert(PRINT_F("test: %10.ls", L"💗💩" ));
	assert(PRINT_F("test: %-10.*ls", -10, L"💗💩" ));
	assert(PRINT_F("test: %-10.3ls", L"💗💩" ));
	assert(PRINT_F("test: %-19.8ls", L"💗💩"));


	/* end of %s tests */

	/* d_i_handler */


  /*   assert(PRINT_F("test: %d", 88));
     assert(PRINT_F("test: %.1d", 90));
     assert(PRINT_F("test: %.20d", 21));
     assert(PRINT_F("test: %.d", 188));;
     assert(PRINT_F("test: %.d", -329));
     assert(PRINT_F("test: %.1d", -90));
     assert(PRINT_F("test: %.20d", -21));
     assert(PRINT_F("test: %.*d", -29, -188));
     assert(PRINT_F("test: %.*d", -30,  90));

    assert(PRINT_F("test: %10d", 90));
     assert(PRINT_F("test: %10d", -21));
     assert(PRINT_F("test: %5d",-567566));
     assert(PRINT_F("test: %4d", 866454));
     assert(PRINT_F("test: %*d", -29, -188));
     assert(PRINT_F("test: %*d", -30,  90));

     assert(PRINT_F("test: %10.1d", 90));
     assert(PRINT_F("test: %10.5d", 90));
     assert(PRINT_F("test: %10.20d", 90));
     assert(PRINT_F("test: %10.1d", -90));
     assert(PRINT_F("test: %10.5d", -90));
     assert(PRINT_F("test: %10.20d", -90));
     assert(PRINT_F("test: %10.d", 155));;
     assert(PRINT_F("test: %9.d", 644));
     assert(PRINT_F("test: %4.d", 87656));
     assert(PRINT_F("test: %10.d", -155));
     assert(PRINT_F("test: %9.d", -644));
     assert(PRINT_F("test: %4.d", -87656));
     assert(PRINT_F("test: %*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %*.*d", 5, 3, -54535454));

     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, -54535454));
     assert(PRINT_F("test: %*.*d", -5, -3, -54535454));
     assert(PRINT_F("test: %*.*d", -5, 3, -54535454));
     assert(PRINT_F("test: %*.*d", 5, -3, -54535454));
     assert(PRINT_F("test: %*.*d", -3, -5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, -5, 155466456));
     assert(PRINT_F("test: %*.*d", -3, 5, 155466456));

	 assert(PRINT_F("test: %-d", 88));
     assert(PRINT_F("test: %-.1d", 90));
     assert(PRINT_F("test: %-.20d", 21));
     assert(PRINT_F("test: %-.d", 188));;
     assert(PRINT_F("test: %-.d", -329));
     assert(PRINT_F("test: %-.1d", -90));
     assert(PRINT_F("test: %-.20d", -21));
     assert(PRINT_F("test: %-.*d", -29, -188));
     assert(PRINT_F("test: %-.*d", -30,  90));

    assert(PRINT_F("test: %-10d", 90));
     assert(PRINT_F("test: %-10d", -21));
     assert(PRINT_F("test: %-5d",-567566));
     assert(PRINT_F("test: %-4d", 866454));
     assert(PRINT_F("test: %-*d", -29, -188));
     assert(PRINT_F("test: %-*d", -30,  90));

     assert(PRINT_F("test: %-10.1d", 90));
     assert(PRINT_F("test: %-10.5d", 90));
     assert(PRINT_F("test: %-10.20d", 90));
     assert(PRINT_F("test: %-10.1d", -90));
     assert(PRINT_F("test: %-10.5d", -90));
     assert(PRINT_F("test: %-10.20d", -90));
     assert(PRINT_F("test: %-10.d", 155));;
     assert(PRINT_F("test: %-9.d", 644));
     assert(PRINT_F("test: %-4.d", 87656));
     assert(PRINT_F("test: %-10.d", -155));
     assert(PRINT_F("test: %-9.d", -644));
     assert(PRINT_F("test: %-4.d", -87656));
     assert(PRINT_F("test: %-*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %-*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %-*.*d", 5, 3, 155466456));
     assert(PRINT_F("test: %-*.*d", 5, 3, -54535454));

     assert(PRINT_F("test: %-*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %-*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %-*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %-*.*d", 3, 5, -54535454));
     assert(PRINT_F("test: %-*.*d", -5, -3, -54535454));
     assert(PRINT_F("test: %-*.*d", -5, 3, -54535454));
     assert(PRINT_F("test: %-*.*d", 5, -3, -54535454));
     assert(PRINT_F("test: %-*.*d", -3, -5, 155466456));
     assert(PRINT_F("test: %-*.*d", 3, -5, 155466456));
     assert(PRINT_F("test: %-*.*d", -3, 5, 155466456));

	 assert(PRINT_F("test: %0d", 88));
     assert(PRINT_F("test: %0.1d", 90));
     assert(PRINT_F("test: %0.20d", 21));
     assert(PRINT_F("test: %0.d", 188));;
     assert(PRINT_F("test: %0.d", -329));
     assert(PRINT_F("test: %0.1d", -90));
     assert(PRINT_F("test: %0.20d", -21));
     assert(PRINT_F("test: %0.*d", -29, -188));
     assert(PRINT_F("test: %0.*d", -30,  90));

    assert(PRINT_F("test: %010d", 90));
     assert(PRINT_F("test: %010d", -21));
     assert(PRINT_F("test: %05d",-567566));
     assert(PRINT_F("test: %04d", 866454));
     assert(PRINT_F("test: %0*d", -29, -188));
     assert(PRINT_F("test: %0*d", -30,  90));

     assert(PRINT_F("test: %010.1d", 90));
     assert(PRINT_F("test: %010.5d", 90));
     assert(PRINT_F("test: %010.20d", 90));
     assert(PRINT_F("test: %010.1d", -90));
     assert(PRINT_F("test: %010.5d", -90));
     assert(PRINT_F("test: %010.20d", -90));
     assert(PRINT_F("test: %010.d", 155));;
     assert(PRINT_F("test: %09.d", 644));
     assert(PRINT_F("test: %04.d", 87656));
     assert(PRINT_F("test: %010.d", -155));
     assert(PRINT_F("test: %09.d", -644));
     assert(PRINT_F("test: %04.d", -87656));
     assert(PRINT_F("test: %0*.*d", -5, 3, 155466456));
     assert(PRINT_F("test: %0*.*d", -5, 3, 155466456));
     assert(PRINT_F("test: %0*.*d", -5, 3, 155466456));
     assert(PRINT_F("test: %0*.*d", -5, 3, -54535454));

     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, 5, -54535454));
     assert(PRINT_F("test: %*.*d", -5, -3, -54535454));
     assert(PRINT_F("test: %*.*d", -5, 3, -54535454));
     assert(PRINT_F("test: %*.*d", 5, -3, -54535454));
     assert(PRINT_F("test: %*.*d", -3, -5, 155466456));
     assert(PRINT_F("test: %*.*d", 3, -5, 155466456));
     assert(PRINT_F("test: %*.*d", -3, 5, 155466456));
	*/

 	/* DBL f handler start */
	double double_max = 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0;
	double normalized_min = 1.0 / 44942328371557897693232629769725618340449424473557664318357520289433168951375240783177119330601884005280028469967848339414697442203604155623211857659868531094441973356216371319075554900311523529863270738021251442209537670585615720368478277635206809290837627671146574559986811484619929076208839082406056034304.0;
	double max_denorm = 4503599627370495.0 / 89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112068608.0;
	max_denorm = max_denorm * 2.0 / 4503599627370496.0;
	double min_denorm = 0.5 / 89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112068608.0   / 1125899906842624.0;

	//just f
	assert(PRINT_F("Biggest double: %f", double_max));
	assert(PRINT_F("\nPlus zero: %f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %.0f\n", 1.5));

	//just #
	assert(PRINT_F("Biggest double: %#f", double_max));
	assert(PRINT_F("\nPlus zero: %#f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %#f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %#.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %#.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %#.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %#f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %#f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %#f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %#.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %#.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %#.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %#.0f\n", 1.5));

	//just +
	assert(PRINT_F("Biggest double: %+f", double_max));
	assert(PRINT_F("\nPlus zero: %+f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+.0f\n", 0.5));
	 assert(PRINT_F("\nrounding zero precision: %+.0f\n", 1.5));


	//just  space
	assert(PRINT_F("Biggest double: % f", double_max));
	assert(PRINT_F("\nPlus zero: % f\n", +0.0));
	assert(PRINT_F("\nMinus zero: % f\n", -0.0));
	assert(PRINT_F("\nNormalized min: % .1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: % .1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: % .1074f\n", min_denorm));
	assert(PRINT_F("\nnan: % f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: % f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: % f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: % .2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: % .5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: % .0f\n", 0.5));
	 assert(PRINT_F("\nrounding zero precision: % .0f\n", 1.5));


	//just width > n
	assert(PRINT_F("Biggest double: %+329f", double_max));
	assert(PRINT_F("\nPlus zero: %+5f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+6f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+1400.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+1300.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+1200.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+14f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+22f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+11f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+9.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+20.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+7.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+8.0f\n", 1.5));


	//just width <= n
	assert(PRINT_F("Biggest double: %+66f", double_max));
	assert(PRINT_F("\nPlus zero: %+1f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+2f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+1.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+5.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+19.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+2f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+1f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+3f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+2.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+4.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+1.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+1.0f\n", 1.5));
	
	//just 0 and width > n
	assert(PRINT_F("Biggest double: %+0329f", double_max));
	assert(PRINT_F("\nPlus zero: %+05f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+06f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+01400.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+01300.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+01200.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+014f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+022f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+011f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+09.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+020.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+07.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+08.0f\n", 1.5));


	//just 0 width <= n
	assert(PRINT_F("Biggest double: %+066f", double_max));
	assert(PRINT_F("\nPlus zero: %+01f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+02f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+01.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+05.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+019.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+02f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+01f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+03f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+02.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+04.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+01.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+01.0f\n", 1.5));


	//just - and  width > n
	assert(PRINT_F("Biggest double: %+-329f", double_max));
	assert(PRINT_F("\nPlus zero: %-+5f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %+-6f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %+-1400.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+-1300.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %-+1200.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+-14f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+-22f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+-11f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+-9.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %-+20.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+-7.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+-8.0f\n", 1.5));


	//just - and width <= n
	assert(PRINT_F("Biggest double: %-+66f", double_max));
	assert(PRINT_F("\nPlus zero: %+-1f\n", +0.0));
	assert(PRINT_F("\nMinus zero: %-+2f\n", -0.0));
	assert(PRINT_F("\nNormalized min: %-+1.1022f\n", normalized_min));
	assert(PRINT_F("\nDenorm max: %+-5.1074f\n", max_denorm));
	assert(PRINT_F("\nDenorm min: %+-19.1074f\n", min_denorm));
	assert(PRINT_F("\nnan: %+-2f\n", 0.0 / 0.0));
	assert(PRINT_F("\n+inf: %+-1f\n", 1.0 / 0.0));
	assert(PRINT_F("\n-inf: %+-3f\n", -1.0 / 0.0));
	assert(PRINT_F("\nrounding only fraction: %+-2.2f\n", 0.125));
	assert(PRINT_F("\nrounding width integer: %+-4.5f\n", 9.9999998));
	assert(PRINT_F("\nrounding zero precision: %+-1.0f\n", 0.5));
	assert(PRINT_F("\nrounding zero precision: %+-1.0f\n", 1.5));
}

int		main(void)
{
	setlocale(LC_ALL, "");
	g_special_random_fd = open("system_printf_output", O_WRONLY | O_TRUNC);
	if (g_special_random_fd != -1)
		start_tests();
	return (0);
}
