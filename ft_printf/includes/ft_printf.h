/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:49:59 by mchau             #+#    #+#             */
/*   Updated: 2021/02/26 17:51:15 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

# define PF_ZERO 0b00000001
# define PF_MINUS 0b00000010
# define PF_PLUS 0b00000100
# define PF_SPACE 0b00001000
# define PF_GRILL 0b00010000

typedef struct	s_fpbits {
	unsigned long	mantissa;
	int				exp;
	char			sign;
}				t_fpbits;

typedef struct	s_fpsource {
	unsigned long	mantissaing;
	unsigned long	mantissafract;
	int				expint;
	int				expfract;
	int				sign;
}				t_fpsource;

typedef struct	s_params
{
	int				precision;
	int				width;
	int             printed;
	unsigned char	length;
	char			flags;
	t_fpsource		*fp;
}				t_params;

typedef struct	s_bigint {
	unsigned long int	digits[87];
	int					dig_num;
}				t_bigint;

int				ft_printf(const char *s, ...);

int				ft_vprintf(char *format, va_list args);

int				ft_parser(char *str, t_params *t, va_list args);

int				print_nchr(char c, int n);

long			ft_strtol(const char *nptr, char **endptr, int base);

int				ft_number_len(unsigned long long input, int radix);

void			ft_putnbr_positive(unsigned long long input, int radix, \
		char start);

int				flag_handler(char flag, t_params *t);

int				convert_to_utf8(unsigned int utf32, unsigned int *utf8);

int				c_handler(t_params *t, va_list arg);

int				s_handler(t_params *t, va_list arg);

int				percent_handler(t_params *t, va_list arg);

int				d_i_handler(t_params *t, va_list arg);

int				p_handler(t_params *t, va_list args);

int				u_handler(t_params *t, va_list args);

int				x_handler(t_params *t, va_list args);

int				x_upper_handler(t_params *t, va_list args);

int				n_handler(t_params *t, va_list args);

int				ft_fp_router(char specific, t_params *t, va_list args);

int				f_handler(t_params *t, va_list args);

int				e_handler(t_params *t, va_list args);

t_bigint		*bigint_constructor(unsigned long value);

void			bigint_print(t_bigint *t);

int    			bigint_multi_short(t_bigint **t, unsigned long value);

int				bigint_round_from(t_bigint *t, int from, int expfract);

int				bigint_summ_short(t_bigint *t, unsigned long value);

void			divide_and_rule(t_bigint *t, unsigned long base, int exp);

int				ft_binpow(int base, int n);

#endif
