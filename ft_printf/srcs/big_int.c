/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:27:54 by mchau             #+#    #+#             */
/*   Updated: 2021/02/25 12:44:59 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int     is_rounding_needed(t_bigint *t, int from);

int g_max = 87;
long int g_base = 1e9;

void	bigint_zero(t_bigint *t)
{
	int i;

	i = 0;
	while (i < g_max)
	{
		t->digits[i] = 0;
		i++;
	}
	t->dig_num = 0;
}

t_bigint	*bigint_constructor(unsigned long value)
{
	int			next;
	t_bigint	*t;

	if (!(t = malloc(sizeof(t_bigint)))) // еще нужно обрабатывать во внешнем вызове
		return (0);
	bigint_zero(t);//change using memset or some similiar
	next = 0;
	while (value)
	{
		t->digits[next] = value % g_base;
		value = value / g_base;
		next++;
	}
	t->dig_num = 1;
	if (next > 0) // t->dig_num gde nibud 0 initialized?
		t->dig_num = (next - 1) * 9 + ft_number_len(t->digits[next - 1], 10);
	return (t);
}

void	bigint_print(t_bigint *t)
{
	int i;

	i = g_max - 1;
	while (i >= 1)
	{
		if (t->digits[i] != 0)
			break;
		i--;
	}
	ft_printf("%u", t->digits[i]);
	if (i == 0)
		return;
	i--;
	while (i >= 0)
	{
		ft_printf("%.9u", t->digits[i]);
		i--;
	}
}

int		bigint_multi_short(t_bigint **t, unsigned long value)
{
	int		carry;
	int		i;
	long	long cur;

	i = 0;
	carry = 0;
	while (i < g_max - 1 || carry)
	{
		cur = carry + (*t)->digits[i] * 1ll * value;
		(*t)->digits[i] = (int)(cur % g_base);
		carry = (int)(cur / g_base);
		i++;
	}
	i = 0;
	while (i < g_max - 1)
	{
		if ((*t)->digits[i] != 0)
			carry = i;
		i++;
	}
	if (carry > 0 && carry != g_max - 1)
		(*t)->dig_num = carry * 9 + ft_number_len((*t)->digits[carry], 10);
	return (1);
}

void	divide_and_rule(t_bigint *t, unsigned long base, int exp)
{

	unsigned long val;

	if (base >= 1e9)
		return;
	val = 1;
	while (exp && val * base < 1e9)
	{
		val *= base;
		exp--;
	}
	bigint_multi_short(&t, val);
	if (exp)
		divide_and_rule(t, base, exp);
}

int		bigint_summ_short(t_bigint *t, unsigned long value)
{
	unsigned long			tmp;
	int						i;

	i = 0;
	while (i < g_max && value)
	{
		tmp = t->digits[i] + value;
		t->digits[i] = tmp % g_base;
		value = tmp / g_base;
		i++;
	}
	if (i > 0)
		t->dig_num = (i - 1) * 9 + ft_number_len(t->digits[i - 1], 10);
	return (1);
}

int		ft_binpow(int base, int n)
{
	int tmp;

	if (n == 0)
		return (1);
	if (n % base != 0)
		return (ft_binpow(base, n-1) * base);
	else
	{
		tmp = ft_binpow(base, n/2);
		return (tmp);
	}
}

int		bigint_round_from(t_bigint *t, int from, int expfract)
{
	int				carry;
	int				n;
	int				tmp;

	if (!is_rounding_needed(t, from - 1))
		return (0);
	n = from / 9;
	t->digits[n] += ft_binpow(10, from % 9);
	carry = t->digits[n] / g_base;
	t->digits[n] %= g_base;
	n++;
	while (n < g_max && carry)
	{
		t->digits[n] += carry;
		carry = t->digits[n] / g_base;
		t->digits[n] %= g_base;
		n++;
	}
	tmp = ft_number_len(t->digits[n - 1], 10);
	if ((n- 1) * 9 + tmp > t->dig_num)
		t->dig_num = (n- 1) * 9 + tmp;
	if ((n - 1) * 9 + tmp > expfract)
	{
		t->digits[n - 1] -= ft_binpow(10, tmp - 1);
		t->dig_num = from;
		return (1);
	}
	return (0);
}

int		is_rounding_needed(t_bigint *t, int from)
{
	int	from_base;
	int	current_value;

	if (from < 0)
		return (0);
	from_base = from / 9;
	from = from % 9;
	current_value = (t->digits[from_base]/ft_binpow(10, from)) % 10;
	if (current_value >= 5)
		return (1);
	return (0);
}

