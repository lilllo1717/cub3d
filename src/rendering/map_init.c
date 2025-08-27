#include "cub3d.h"

//player_delta_x and y represent the movement vector of the player, the direction and speed the player moves when pressing movement keyes.
//x is horizontal forward direction
//y is vertical forward direction
//cos(player_angle) * 5: speed is 5. player moves 5 pixels per keypress
void create_world(void *param)
{
	mlx_image_t	* tile;
	t_render	*render;

	render = (t_render *)param;
	uint32_t color;
	//uint32_t	i;
	int	x = 0;
	int map_s = 77;
	int y = 0;
	int	xo = 0;
	int yo = 0;
	int map_x = 25;
	int map_y = 14;
	int map[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	ft_memcpy(render->map, map, sizeof(map));
	
	tile = mlx_new_image(render->mlx, WIDTH, HEIGHT);
    if (!tile)
		return;
	ft_memset(tile->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (y < map_y)
	{
		x = 0; 
		while (x < map_x)
		{
			printf("y: [%d]\nmap_x: [%d]\nx: [%d]\n", y, map_x, x);
			if (render->map[y * map_x + x] == 2)
			{
				printf("x: [%d]\n", x);
				printf("y: [%d]\n", y);
				render->player_x = (float)(x * map_s) + (map_s / 2);
				render->player_y = (float)(y * map_s) + (map_s / 2);
			}
			printf("passed\n");
			if (render->map[y * map_x + x] == 1)
				color = WALL;
			else
				color = FLOOR;
			xo = x * map_s;
			yo = y * map_s;
			put_tile(tile, xo, yo, map_s, color);
			x++;
		}
		y++;
	}
	render->ray_image = mlx_new_image(render->mlx, WIDTH, HEIGHT);
	if (!render->ray_image)
		return ;
	ft_memset(render->ray_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	mlx_image_to_window(render->mlx, tile, 0, 0);
	mlx_image_to_window(render->mlx, render->ray_image, 0, 0);
	render->player_delta_x = cos(render->player_angle) * 5;
	render->player_delta_y = sin(render->player_angle) * 5;
}

void	put_tile(mlx_image_t *image, int start_x, int start_y, int size, uint32_t color)
{
	int	x;
	int y;

	y = start_y + 1;
	x = start_x + 1;
	while (y < start_y + size - 1)
	{
		x = start_x + 1;
		while (x < start_x + size -1)
		{
			if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
				mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(void *param)
{
	t_render	*render;
	float		pixel_x;
	float		pixel_y;
	float		y;
	float		x;

	y = 0;
	x = 0;
	render = (t_render *)param;
	if (!render->player_image)
	{
		render->player_image = mlx_new_image(render->mlx, WIDTH, HEIGHT);
		if (mlx_image_to_window(render->mlx, render->player_image, 0,  0) < 0)
			return ;
	}
	
	ft_memset(render->player_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	pixel_x = render->player_x;
	pixel_y = render->player_y;
	printf("player x: [%f]\n", render->player_x);
	printf("player y: [%f]\n", render->player_y);
	put_tile(render->player_image, (int)pixel_x - 5, (int)pixel_y - 5, 10 , PLAYER_COLOR);
	
}
