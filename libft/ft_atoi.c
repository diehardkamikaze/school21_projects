/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 05:12:47 by mchau             #+#    #+#             */
/*   Updated: 2020/11/12 03:53:54 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		base_situation(int base, int *i, const char *nptr)
{
	int iter;

	iter = *i;
	if (base == 16 && nptr[iter] == '0')
	{
		iter++;
		if (nptr[iter] == 'x')
			iter++;
	}
	if (base == 0)
	{
		base = 10;
		if (nptr[iter] == '0')
		{
			base = 8;
			iter++;
			if (nptr[iter] == 'x')
			{
				base = 16;
				iter++;
			}
		}
	}
	*i = iter;
	return (base);
}

char	get_decimal_number(char symb, int base)
{
	int	current_num;

	if (ft_isdigit(symb))
		current_num = symb - '0';
	else if (ft_isalpha(symb))
	{
		if (symb >= 'A' && symb <= 'Z')
			symb = symb + 32;
		current_num = symb - 'a' + 10;
	}
	else
		return (-1);
	if (current_num < base)
		return (current_num);
	return (-1);
}

long	is_overflowed(long result, int sign)
{
	long ret;

	ret = 1;
	if (sign == -1 && result * (long)sign > 0)
		ret = LONG_MIN;
	if (sign == 1 && result * (long)sign < 0)
		ret = LONG_MAX;
	return (ret);
}

long	special_strtol(const char *nptr, char **endptr, int base)
{
	long	result;
	int		i;
	long	temp;
	long	sign;
	long	overflowed;

	sign = 1;
	i = 0;
	result = 0;
	overflowed = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	base = base_situation(base, &i, nptr);
	while ((temp = get_decimal_number(nptr[i++], base)) != -1)
	{
		result = result * (long)base + temp;
		if (overflowed == 1)
			overflowed = is_overflowed(result, sign);
	}
	if (endptr)
		*endptr = (char *)(nptr + i - 1);
	return (overflowed != 1 ? overflowed : result * sign);
}

int		ft_atoi(const char *str)
{
	return ((int)special_strtol(str, 0, 10));
}
