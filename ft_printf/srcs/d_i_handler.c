/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_i_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 09:05:01 by mchau             #+#    #+#             */
/*   Updated: 2021/01/22 10:30:56 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	inner_long_handler(unsigned char length, va_list args)
{
	if (length == 'h')
		return ((short int)va_arg(args, int));
	if (length == 'h' + 'h')
		return ((char)va_arg(args, int));
	if (length == 'l')
		return (va_arg(args, long int));
	if (length == 'l' + 'l')
		return (va_arg(args, long long int));
	return (va_arg(args, int));
}

char		get_sign(char flags)
{
	if (flags & PF_PLUS)
		return (
}

int			d_i_handler(t_params *t, va_list arg)
{
	long long			temp;
	unsigned long long	d;
	int					result_count;
	int					sign;
	char				sign_symb;

	temp = inner_long_handler(t->length, arg);
	if (temp < 0)
		
	if (!(t-flag & PF_MINUS))
		print_nchr(fill, t->width);
	print_nchr('0', t->precision);
		if (d != 0 || t->precision != 0)
		ft_putnbr_positive(d, 10, 'a');
	else
		result_count--;
	if (t-flag & PF_MINUS)
		print_nchr(fill, t->width);
	return (t->precision + t->width + result_count + sign);
}
