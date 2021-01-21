/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:55:56 by mchau             #+#    #+#             */
/*   Updated: 2021/01/20 12:59:04 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		convert_to_utf8(unsigned int utf32, unsigned int *utf8)
{
	unsigned int	byte_4;
	unsigned int	byte_3;
	unsigned int	byte_2;
	unsigned int	byte_1;

	if (utf32 <= 127 && (*utf8 = utf32))
		return (1);
	byte_4 = utf32 % 64;
	byte_3 = utf32 / 64 % 64;
	if (utf32 <= 2047 && (*utf8 = (byte_4 + 128) * 256 + (byte_3 + 192)))
		return (2);
	byte_2 = (utf32 / 4096) % 64;
	if (utf32 <= 65535)
	{
		*utf8 = ((byte_4 + 128) * 256 + (byte_3 + 128)) * 256 + (byte_2 + 224);
		return (3);
	}
	byte_1 = (utf32 / 131072) % 64;
	if (utf32 <= 1114111)
	{
		*utf8 = ((byte_4 + 128) * 65536 + (byte_3 + 128) * 256\
				+ (byte_2 + 128)) * 256 + (byte_1 + 240);
		return (4);
	}
	return (0);
}

int		ft_putstr(char *s, wchar_t *s2)
{
	int				c_len;
	int				len;
	unsigned int	character;

	len = 0;
	if (s != 0)
	{
		while (*s != 0)
		{
			len += write(1, s, 1);
			s++;
		}
		return (len);
	}
	if (s2 != 0)
		while (*s2 != 0)
		{
			c_len = convert_to_utf8(*s2, &character);
			len += write(1, &character, c_len);
			s2++;
		}
	return (len);
}

void	print_nchr(char c, int n)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}
