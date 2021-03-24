/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_game_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:03:28 by mchau             #+#    #+#             */
/*   Updated: 2021/03/24 19:01:13 by mchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
/*
void	sort_all_sprites(int *sprite_order, int *sprite_distance, int len)
{
	// do normal fast sort
}
*/
unsigned int *get_world_side_txt(t_all *t, int side, float dir_x, float dir_y, int *wi, int *hi)
{
	int num;

	if (dir_x > 0 && dir_y >= 0)
	{
		if (side == 1)
			num = EA_TXT;
		else
			num = SO_TXT;
	}
	if (dir_x >= 0 && dir_y < 0)
	{
		if (side == 1)
			num = WE_TXT;
		else
			num = SO_TXT;
	}
	if (dir_x < 0 && dir_y <= 0)
	{
		if (side == 1)
			num = WE_TXT;
		else
			num = NO_TXT;
	}

	if (dir_x <= 0 && dir_y > 0)
	{
		if (side == 1)
			num = EA_TXT;
		else
			num = NO_TXT;
	}

	return ((unsigned int *)mlx_get_data_addr_main(t->txt_img[num], wi, hi));
}

void	fill_image_by_map(t_all *t)
{
	float posX = t->plr->x;
	float posY = t->plr->y;
	float dirX = t->plr->dirX;
	float dirY = t->plr->dirY;
	float planeX = t->plr->planeX;
	float planeY = t->plr->planeY;
	float z_buffer[t->maze->w_h / 1000000];

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

	  int g = 0;
	  while (g++ < drawStart)
		  t->game.addr[g * w + x] = t->maze->c_f[0];

	  double wallX;
      if(side == 0) wallX = posY + perpWallDist * rayDirY;
      else          wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));


	int texWidth;
	int texHight;
	 unsigned int *texture;
	  texture = get_world_side_txt(t, side, rayDirX, rayDirY, &texWidth, &texHight);

      int texX = (int)(wallX * (double)texWidth);

      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

	  double step = 1.0 * texHight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      while(drawStart < drawEnd)
      {
        int texY = (int)texPos & (texHight - 1);
        texPos += step;
        unsigned int color = texture[texHight * texY + texX];

        if(side == 1) color = (color >> 1) & 8355711;
        t->game.addr[drawStart * w + x] = color;
		drawStart++;
      }
	  /*	  while (drawStart < drawEnd)
	  {
			t->game.addr[drawStart * w + x] = color;
			drawStart++;
	  } */
	  if (drawEnd >= 0)
	  	while (drawEnd < h)
	  	{
			  t->game.addr[drawEnd * w + x] = t->maze->c_f[1];
			  drawEnd++;
	  	}
	  z_buffer[x] = perpWallDist;
	  x++;
	}
	int i = 0;
	int sprite_order[t->spr_len];
	float sprite_distance[t->spr_len];
	while (i < t->spr_len)
    {
		sprite_order[i] = i;
		sprite_distance[i] = ((posX - t->spr[i] / 1000) * (posX - t->spr[i] / 1000) + (posY - t->spr[i] % 1000) * (posY - t->spr[i] % 1000));
		i++;
	}
	//sort_all_sprites(sprite_order, sprite_distance, t->spr_len);
	i = 0;
	while (i < t->spr_len)
	{
		float sprite_x = t->spr[sprite_order[i]] / 1000 + 0.5 - posX;
		float sprite_y = t->spr[sprite_order[i]] % 1000 + 0.5 - posY;
		float invDet = 1.0 / (planeX * dirY - dirX * planeY);
		float transformX = invDet * (dirY * sprite_x - dirX * sprite_y);
		float transformY = invDet * (-planeY * sprite_x + planeX * sprite_y);
		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));
		#define uDiv 1
     	#define vDiv 1
      	#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);
		int spriteHeight = abs((int)(h / (transformY))) / vDiv;

		int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
      	if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
        if (drawEndY >= h)
			drawEndY = h - 1;
		int spriteWidth = abs((int) (h / (transformY))) / uDiv;

		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
	  	if (drawEndX >= w)
			drawEndX = w - 1;
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * t->txt_size[0] / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        	if (transformY > 0 && stripe > 0 && stripe < w && transformY < z_buffer[stripe])
			{
        		for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        		{
        		int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          		int texY = ((d * t->txt_size[1]) / spriteHeight) / 256;

				int z[3];
				unsigned int *tmp =  (unsigned int *)(mlx_get_data_addr(t->txt_img[SPR_TXT], z, z+1, z+2));
          		unsigned int color = tmp[t->txt_size[0] * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0)
					t->game.addr[y * w + stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
      }
	  i++;
	}
}


void init_txt_array(t_all *t)
{
	int i;
	int width;
	int height;

	i = 0;
	t->txt_img[i] = mlx_xpm_file_to_image(t->game.mlx, \
			t->maze->textures[i], t->txt_size, t->txt_size + 1);
	while (i < 5)
	{
		t->txt_img[i] = mlx_xpm_file_to_image(t->game.mlx, \
				t->maze->textures[i], &width, &height);
		if (t->txt_img[i] == 0)
			exit_with_message("Invalid texture", t);
		if (width != t->txt_size[0] || height != t->txt_size[1])
			exit_with_message("Problem with texture sizes", t);
		i++;
	}
}

void	init_game (t_all *t)
{
	int	bpp;
	int	size_line;
	int	endian;

	if (!(t->game.mlx = mlx_init()))
		exit_with_message("GAME: mlx_init malloc error", t);
	if(!(t->game.img = mlx_new_image(t->game.mlx, t->maze->w_h / 1000000, t->maze->w_h % 1000000)))
		exit_with_message("GAME: mlx_image_init malloc error", t);

	t->game.addr = (unsigned int *)(mlx_get_data_addr(t->game.img, &bpp, &size_line, &endian)); 
	init_txt_array(t);
	fill_image_by_map(t);
}


void	go_game_logic(t_all *t)
{
	if (!(t->game.win = mlx_new_window(t->game.mlx, (int)(t->maze->w_h / 1000000),\
					(int)(t->maze->w_h % 1000000), "mchau")))
		exit_with_message("GAME: mlx_new_window malloc error", t);
	mlx_put_image_to_window(t->game.mlx, t->game.win, t->game.img, 0, 0);
	mlx_hook(t->game.win, 17, 0, exit_handler, t);
	mlx_hook(t->game.win, 2, 0, key_press_handler, t);
	mlx_hook(t->game.win, 3, 0, key_release_handler, t);
	mlx_loop_hook(t->game.mlx, key_state_checker, t);
	mlx_loop(t->game.mlx);
}
