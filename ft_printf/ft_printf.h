/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:49:59 by mchau             #+#    #+#             */
/*   Updated: 2021/01/15 13:51:42 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_params
{
	int		width;
	int		precision;
	int		(*specific)(struct s_params *t);
	char	zero;
	char	minus;
}				t_params;

int				ft_printf(const char *s, ...);

int				ft_vprintf(char *format, va_list args);

int				func_n(void *n, ...);

void			init_parsing_handlers(int (**handlers)(char *, t_params *));

long			ft_strtol(const char *nptr, char **endptr, int base);

char			*ft_strchr(const char *s, int c);

int				spec_handler(char flag, t_params *t);

int				flag_handler(char flag, t_params *t);

#endif
