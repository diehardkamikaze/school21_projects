/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:03:28 by mchau             #+#    #+#             */
/*   Updated: 2021/03/23 11:39:27 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"

void	fill_image_by_map(t_all *t)
{
	if(!(t->game->img = mlx_new_image(t->game->mlx, t->maze->w_h / 1000000, t->maze->w_h % 1000000)))
		exit_with_message("GAME: mlx_image_init malloc error", t);

	int bpp;
	int size_line;
	int endian;

	t->game->addr = (unsigned int *)(mlx_get_data_addr(t->game->img, &bpp, &size_line, &endian)); // polu4aem buffer
	float posX = t->plr->x;
	float posY = t->plr->y;
	float dirX = t->plr->dirX;
	float dirY = t->plr->dirY;
	float planeX = t->plr->planeX;
	float planeY = t->plr->planeY;

	int x = 0;
	int w = t->maze->w_h / 1000000;
	int h =	t->maze->w_h % 1000000;
	while (x < w)
	{
		float cameraX = 2 * x / (float)w - 1;
		float rayDirX = dirX + cameraX * planeX;
		float rayDirY = dirY + cameraX * planeY;
		int mapX = (int)posX;
		int mapY = (int)posY;


		float sideDistX;
    	float sideDistY;
		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);
		float perpWallDist;

		int stepX;
      	int stepY;

		int hit = 0;
      	int side;
		if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
	  while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (t->map[mapX][mapY] == '1') hit = 1;
      }
	  if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

	  int color;
	  if (side == 1)
		color = 0xFFFF00;
	  else color = 0x800000;
      //draw the pixels of the stripe as a vertical line
	  int g = 0;
	  while (g++ < drawStart)
		  t->game->addr[g * w + x] = t->maze->c_f[0];
	  while (drawStart < drawEnd)
	  {
			t->game->addr[drawStart * w + x] = color;
			drawStart++;
	  }
	  while (drawEnd++ < h - 1)
		  t->game->addr[drawEnd * w + x] = t->maze->c_f[1];
	  x++;
	}

	mlx_put_image_to_window(t->game->mlx, t->game->win, t->game->img, 0, 0);
}

void	scale_pixel(t_all *t, int x, int y, int color)
{
	int i;
	int j;
	int size;

	size = 20;
	x = size * x;
	y = size * y;
	i = -1;
	j = -1;
	while (++i < size && (j = -1))
		while (++j < size)
			t->game->addr[(x + i) * t->maze->w_h / 1000000 + (y + j)] = color;
}
void	go_game_logic(t_all *t)
{
	t_win game;

	t->game = &game;
	if (!(game.mlx = mlx_init()))
		exit_with_message("GAME: mlx_init malloc error", t);
	//preprocess window reso situation
	if (!(game.win = mlx_new_window(game.mlx, (int)(t->maze->w_h / 1000000),\
					(int)(t->maze->w_h % 1000000), "mchau")))
		exit_with_message("GAME: mlx_new_window malloc error", t);
	fill_image_by_map(t);
	mlx_hook(game.win, 17, 0, exit_handler, t);
	mlx_hook(game.win, 2, 0, &key_handler, t);
	mlx_hook(game.win, 3, 0, &key_handler2, t);
	mlx_loop_hook(game.mlx, key_state_checker, t);
	mlx_loop(game.mlx);
}
