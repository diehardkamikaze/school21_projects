/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:49:59 by mchau             #+#    #+#             */
/*   Updated: 2021/01/20 14:38:03 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <wchar.h>

# define PF_ZERO 1
# define PF_MINUS 2
# define PF_PLUS 4
# define PF_SPACE 8
# define PF_GRILL 16

typedef struct	s_params
{
	int		precision;
	int		width;
	int		length;
	char	flags;
}				t_params;

int				ft_printf(const char *s, ...);

int				ft_vprintf(char *format, va_list args);

void			print_nchr(char c, int n);

long			ft_strtol(const char *nptr, char **endptr, int base);

char			*ft_strchr(const char *s, int c);

int				ft_number_len(unsigned long input, int radix);

void			ft_putnbr_positive(unsigned long input, int radix, char start);

void			spec_handler(char flag, t_params *t);

int				flag_handler(char flag, t_params *t);

int				ft_putstr(char *s, wchar_t *s2);

int				convert_to_utf8(unsigned int utf32, unsigned int *utf8);

int				c_handler(t_params *t, va_list arg);

int				s_handler(t_params *t, va_list arg);

int				percent_handler(t_params *t, va_list arg);

int				d_i_handler(t_params *t, va_list arg);

int				p_handler(t_params *t, va_list args);

int				u_handler(t_params *t, va_list args);

int				x_handler(t_params *t, va_list args);

int				x_upper_handler(t_params *t, va_list args);

#endif
