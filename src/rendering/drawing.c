#include "cub3d.h"

int	draw_line(t_render *render, int begin_x, int begin_y, int end_x, int end_y)
{
	float	delta_x;
	float	delta_y;
	float	current_x;
	float	current_y;
	float	step_x;
	float	step_y;
	int		steps;
	int		i;

	i = 0;
	// deltas are the total horizontal and vertical distance from start point to end point.
	//		positive delta y - line goes down
	//		negative delta y - line goes up
	// 		0 - horizontal line
	delta_y = end_y - begin_y;

	//		positive delta x - line goes right
	//		negative delta x - line goes left
	// 		0 - vertical line
	delta_x = end_x - begin_x;

	steps = determine_steps(delta_x, delta_y);
	// printf("steps [%d\n", steps);

	// steps calculate the incremental step sizes needed to draw a consistent line between 2 points
	step_x = delta_x / steps;
	step_y = delta_y / steps;
	//current initializes the starting position for the line drawing by setting the current drawing coordinates to the beggining of the point line
	current_x = begin_x;
	current_y = begin_y;
	
	//we put pixels until we have as many as the steps calculated before, we use the current variables to have the starting position of the ray
	while (i <= steps)
	{
		//only drawing rays on right half of the window
		if ((int)current_x >= 0 && (int)current_x < WIDTH && 
				(int)current_y >= 0 && (int)current_y < HEIGHT)
			mlx_put_pixel(render->ray_image, (int)current_x, (int)current_y, 0xFF0000FF);
		current_x += step_x;
		current_y += step_y;
		i++;
	}
	// printf("[%f]\n", render->ray_angle);
	
	return (0);
}

static uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*pixel;
	uint32_t color;

	if (!texture || x < 0 || y < 0 || x >= (int)texture->width || y >= (int)texture->height)
		return (0x000000); // black for invalid coordinates
	// calculates the pixel position in the texture data
	pixel = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	// combines the rgba values into a single uint32_t
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

	return (color);
}

void draw_col(t_game *game)
{
    mlx_texture_t	*hit_wall_texture;
    int				tex_x;
	int				tex_y;
    float			texture_step;
	float			texture_y_offset;
    int				y;
	uint32_t		pixel_color; 
    int				wall_start;
    int				wall_end;

	hit_wall_texture = select_correct_texture(game);
	tex_x = (int)get_xcoord_from_texture(game);
	texture_step = (float)hit_wall_texture->height / (float)game->render->line_height;
	wall_start = (HEIGHT / 2) - (game->render->line_height / 2);
	wall_end = wall_start + game->render->line_height;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall_start)
			mlx_put_pixel(game->render->ray_image, game->render->ray, y, game->colors->c_rgb); // ceiling
		else if (y >= wall_end)
			mlx_put_pixel(game->render->ray_image, game->render->ray, y, game->colors->f_rgb); //floor
		else
		{
			// calculate texture y offset coordinate relative to wall start
			texture_y_offset = (y - wall_start) * texture_step;
			tex_y = (int)texture_y_offset;
			if (tex_y < 0) 
				tex_y = 0;
			if (tex_y >= (int)hit_wall_texture->height) 
				tex_y = hit_wall_texture->height - 1;
			pixel_color = get_texture_pixel(hit_wall_texture, tex_x, tex_y);
			mlx_put_pixel(game->render->ray_image, game->render->ray, y, pixel_color);
		}
		y++;
	}
}

mlx_texture_t *select_correct_texture(t_game *game)
{
	if (game->render->wall_dir == NORTH)
		return(game->textures->north_t);
	else if (game->render->wall_dir == SOUTH)
		return(game->textures->south_t);
	else if (game->render->wall_dir == EAST)
		return(game->textures->east_t);
	else if (game->render->wall_dir == WEST)
		return(game->textures->west_t);
	else
		return (NULL);
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
		game->render->player_image = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
		player_inst = mlx_image_to_window(game->render->mlx, game->render->player_image, 0,  0);
		printf("id [%d]\n", player_inst);
		mlx_set_instance_depth(game->render->player_image->instances, 3);
	}
	ft_memset(game->render->player_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	pixel_x = (game->render->player_x / TILE) * MINITILE + 16;
	pixel_y = (game->render->player_y / TILE) * MINITILE + 16;
	put_tile(game->render->player_image, (int)pixel_x - 5, (int)pixel_y - 5, PLAYER_COLOR);
}
