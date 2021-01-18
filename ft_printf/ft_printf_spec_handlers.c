/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specificators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:41:33 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 11:40:40 by mchau            ###   ########.fr       */
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
	if (s == 0)
		s = "(null)";
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

int	d_i_handler(t_params *t, va_list arg)
{
	long	d;
	int		np;
	int		n;
	int		result_count;
	int		is_negative;
	char	fill;

	fill = ' ';
	is_negative = 0;
	np = 0;
	n = 0;
	d = (long)va_arg(arg, int);
	if (d < 0 && (is_negative = 1))
		d = d * (-1);
	if (t->zero && !t->dot)
		fill = '0';
	result_count = ft_number_len(d, 10);
	if (t->dot && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && d == 0)
		result_count--;
	n = (t->width > np + result_count + is_negative) ?
		t->width - np - result_count - is_negative : 0;
	if (is_negative && fill == '0')
		write(1, "-", 1);
	if (!t->minus)
		print_nchr(fill, n);
	if (is_negative && !(fill == '0'))
		write(1, "-", 1);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(d, 10, 'a');
	if (t->minus)
		print_nchr(fill, n);
	return (np + n + is_negative + result_count);
}

int	p_handler(t_params *t, va_list args)
{
	int result_count;
	unsigned long p;
	int n;

	p = va_arg(args, unsigned long);
	result_count = 2 + ft_number_len(p, 16);
	n = t->width > result_count ? t->width - result_count : 0;
	if (!t->minus)
		print_nchr(' ', n);
	write(1, "0x", 2);
	ft_putnbr_positive(p, 16, 'a');
	if (t->minus)
		print_nchr(' ', n);
	return (result_count + n);
}

int	u_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	u;
	int				np;
	int				n;
	char			fill;

	u = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(u, 10);
	np = 0;
	n = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && u == 0)
		result_count--;
	if (t->width > np + result_count)
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(u, 10, 'a');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}

int	x_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	x;
	int				np;
	int				n;
	char			fill;

	x = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(x, 16);
	np = 0;
	n = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && x == 0)
		result_count--;
	if (t->width > np + result_count)
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(x, 16, 'a');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}

int	x_upper_handler(t_params *t, va_list args)
{
	int				result_count;
	unsigned int	x;
	int				np;
	int				n;
	char			fill;

	x = va_arg(args, unsigned int);
	if ((fill = ' ') && t->zero)
		fill = '0';
	result_count = ft_number_len(x, 16);
	np = 0;
	n = 0;
	if (t->dot && (fill = ' ') && t->precision > result_count)
		np = t->precision - result_count;
	if (t->dot && t->precision == 0 && x == 0)
		result_count--;
	if (t->width > np + result_count)
		n = t->width - np - result_count;
	if (!t->minus)
		print_nchr(fill, n);
	print_nchr('0', np);
	if (result_count)
		ft_putnbr_positive(x, 16, 'A');
	if (t->minus)
		print_nchr(fill, n);
	return (result_count + np + n);
}
