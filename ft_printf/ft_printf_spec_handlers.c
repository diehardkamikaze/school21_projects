/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specificators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:41:33 by mchau             #+#    #+#             */
/*   Updated: 2021/01/17 14:00:37 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nchr(char c, int n)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}

int	c_handler(t_params *t, va_list arg)
{
	char	c;
	int		result_count;
	int		n;

	c = (char)va_arg(arg, int);
	n = t->width > 1 ? t->width - 1 : 0;
	result_count = 1;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, &c, 1);
	if(t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int	s_handler(t_params *t, va_list arg)
{
	char	*s;
	int		result_count;
	int		n;

	result_count = 0;
	s = (char *)va_arg(arg, void *);
	while (s[result_count] != 0)
		result_count++;
	if (t->dot && t->precision >= 0 && result_count > t->precision)
		result_count = t->precision;
	n = t->width > result_count ? t->width - result_count : 0;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, s, result_count);
	if (t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int	percent_handler(t_params *t, va_list arg)
{
	int		result_count;
	char	fill;
	int		n;

	if (arg)
		result_count = 1;
	result_count = 1;
	fill = t->zero ? '0' : ' ';
	n = t->width > 1 ? t->width - 1 : 0;
	if (!t->minus)
		print_nchr(fill, n);
	write(1, "%", 1);
	if (t->minus)
		print_nchr(fill, n);
	return (n + result_count);
}

/*


s_handler
p_handler
d_handler
u_handlex
x_handler
percent_handler
*/
