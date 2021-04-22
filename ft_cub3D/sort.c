/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:27:40 by mchau             #+#    #+#             */
/*   Updated: 2021/04/22 18:00:33 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cub3d.h>

void	sort_all_sprites(int *sprite_order, double *sprite_distance, int len)
{
	int		i;
	int		j;
	double	tmp;

	i = 1;
	while (i < len)
	{
		j = 0;
		while (j < len - i)
		{
			if (sprite_distance[j] < sprite_distance[j + 1])
			{
				tmp = sprite_distance[j];
				sprite_distance[j] = sprite_distance[j + 1];
				sprite_distance[j + 1] = tmp;
				sprite_order[j] = sprite_order[j] ^ sprite_order[j + 1];
				sprite_order[j + 1] = sprite_order[j] ^ sprite_order[j + 1];
				sprite_order[j] = sprite_order[j] ^ sprite_order[j + 1];
			}
			j++;
		}
		i++;
	}
}
