/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf_codings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:24:28 by mchau             #+#    #+#             */
/*   Updated: 2021/01/21 11:25:26 by mchau            ###   ########.fr       */
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
