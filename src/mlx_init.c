/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:12 by rojornod          #+#    #+#             */
/*   Updated: 2025/08/21 16:16:11 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(void *param)
{
	t_render	*render;
	float		pixel_x;
	float		pixel_y;

	render = (t_render *)param;
	if (!render->player_image)
	{
		render->player_image = mlx_new_image(render->mlx, WIDTH, HEIGHT);
		if (mlx_image_to_window(render->mlx, render->player_image, 0, 0) < 0)
			return ;
	}
	ft_memset(render->player_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	pixel_x = render->player_x;
	pixel_y = render->player_y;
	if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
		mlx_put_pixel(render->player_image, (int)pixel_x,
			(int)pixel_y, PLAYER_COLOR);
}

t_render	*init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	ft_memset(render, 0, sizeof(t_render));
	return (render);
}

void	mlx_start(t_render *render)
{
	render->mlx = mlx_init(WIDTH, HEIGHT, "BEST GAME EVER", true);
	if (!render->mlx)
	{
		perror("Failed to initialize MLX42");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(render->mlx, &key_handler, render);
	draw_player(render);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_render	*render;

	render = (t_render *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_putendl_fd("Goodbye", 1);
		mlx_close_window(render->mlx);
	}
	if (mlx_is_key_down(render->mlx, MLX_KEY_W))
		render->player_y -= MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_S))
		render->player_y += MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_D))
		render->player_x += MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_A))
		render->player_x -= MOVEMENT;
	draw_player(render);
}

void create_world(void *param)
{
	mlx_image_t	* wall;
	t_render	*render;

	render = (t_render *)param;
	uint32_t color;
	uint32_t	i;
	int	x;
	int map_s = 64;
	int y = 0;
	int	xo = 0;
	int yo = 0;
	int map_x = 8;
	int map_y = 8;
	int map[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 1, 1,
		1, 0, 1, 0, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};
	
	wall = mlx_new_image(render->mlx, WIDTH, HEIGHT);
    if (!wall)
		return;
	while(y < map_y)
	{
		while (x < map_x)
		{
			if (map[y * map_x + x] == 1)
			{
				color = 0xFFFFFFFF;
			}
			else
				color = 0x00000000;
			xo = x * map_s;
			yo = y * map_s;
		}
		y++;
	}

}


/*
	need to translate this into mlx42
*/

// void drawMap2D()
// {
//  int x,y,xo,yo;
//  for(y=0;y<mapY;y++)
//  {
//   for(x=0;x<mapX;x++)
//   {
//    if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
//    xo=x*mapS; yo=y*mapS;
//    glBegin(GL_QUADS); 
//    glVertex2i( 0   +xo+1, 0   +yo+1); 
//    glVertex2i( 0   +xo+1, mapS+yo-1); 
//    glVertex2i( mapS+xo-1, mapS+yo-1);  
//    glVertex2i( mapS+xo-1, 0   +yo+1); 
//    glEnd();
//   } 
//  } 


 
