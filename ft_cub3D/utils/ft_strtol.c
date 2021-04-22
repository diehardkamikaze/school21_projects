/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:25:30 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 17:58:17 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (c);
	return (0);
}

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

	if (symb >= '0' && symb <= '9')
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

long	ft_strtol(const char *nptr, char **endptr, int base)
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
		*endptr = (char *)(nptr + (i - 1));
	return (overflowed != 1 ? overflowed : result * sign);
}
