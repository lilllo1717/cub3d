#include "cub3d.h"

void create_world(void *param)
{
	mlx_image_t	*tile;
	t_game		*game;
	uint32_t	color;
	int			x = 0;
	int 		y = 0;
	int			xo = 0;
	int 		yo = 0;
	int			tile_instance;
	// int			ray_instance;

	
	game = (t_game *)param;
	if (!game->render) {
		printf("ERROR: Invalid game->render or game->map is NULL\n");
		return ;
	}
	if (!game->map) 
	{
   		 printf("ERROR: render->map is NULL!\n");
    	return;
	}
	tile = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
	
    if (!tile)
		return;
	ft_memset(tile->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (y < (int)game->map_info.num_rows)
	{
		x = 0; 
		while (x < (int)game->map_info.max_len)
		{

			if (game->map[y][x] == '1')
				color = WALL;
			else if (game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' 
				|| game->map[y][x] == 'W' || game->map[y][x] == 'E')
				color = FLOOR;
			else
				color = EMPTY;
			xo = x * MINITILE;
			yo = y * MINITILE;
			if (xo < (WIDTH) && yo < HEIGHT)
				put_tile(tile, xo, yo, MINITILE, color);
			x++;
		}
		y++;
	}
	game->render->ray_image = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
	if (!game->render->ray_image)
		return ;
	mlx_image_to_window(game->render->mlx, game->render->ray_image, 0, 0);
	mlx_set_instance_depth(game->render->ray_image->instances, 0);
	ft_memset(game->render->ray_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	tile_instance = mlx_image_to_window(game->render->mlx, tile, 16, 16);
	
	mlx_set_instance_depth(tile->instances, 2);
	game->render->player_delta_x = cos(game->render->player_angle) * 5;
	game->render->player_delta_y = sin(game->render->player_angle) * 5;
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
	t_game		*game;
	float		pixel_x;
	float		pixel_y;
	int			player_inst;

	game = (t_game *)param;
	if (!game->render->player_image)
	{
		// printf("player image is null, creating image\n");
		game->render->player_image = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
		player_inst = mlx_image_to_window(game->render->mlx, game->render->player_image, 0,  0);
		printf("id [%d]\n", player_inst);
		mlx_set_instance_depth(game->render->player_image->instances, 3);
	}
	ft_memset(game->render->player_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	pixel_x = (game->render->player_x / TILE) * MINITILE + 16;
	pixel_y = (game->render->player_y / TILE) * MINITILE + 16;
	put_tile(game->render->player_image, (int)pixel_x - 5, (int)pixel_y - 5, 10, PLAYER_COLOR);
}
