/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:49:59 by mchau             #+#    #+#             */
/*   Updated: 2021/01/18 09:31:41 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h> //del that!
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_params
{
	int		precision;
	int		width;
	int		(*specific)(struct s_params *t, va_list args);
	char	zero;
	char	minus;
	char	dot;
}				t_params;

int				ft_printf(const char *s, ...);

int				ft_vprintf(char *format, va_list args);

int				func_n(void *n, ...);

void			init_parsing_handlers(int (**handlers)(char *, t_params *));

long			ft_strtol(const char *nptr, char **endptr, int base);

char			*ft_strchr(const char *s, int c);

int				ft_number_len(unsigned long input, int radix);

void			ft_putnbr_positive(unsigned long input, int radix, char start);

int				spec_handler(char flag, t_params *t);

int				flag_handler(char flag, t_params *t);

int				error_log(char *flag, char *message);

void			ft_putstr(char *s);

int				c_handler(t_params *t, va_list arg);

int				s_handler(t_params *t, va_list arg);

int				percent_handler(t_params *t, va_list arg);

int				d_i_handler(t_params *t, va_list arg);

int				p_handler(t_params *t, va_list args);

int				u_handler(t_params *t, va_list args);

int             x_handler(t_params *t, va_list args);

int             x_upper_handler(t_params *t, va_list args);

#endif
