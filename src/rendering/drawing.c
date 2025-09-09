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
// void	put_textures(t_game *game, int wall_start, int wall_end, int col_x, int y)
// { 
// 	int		i;
// 	uint8_t	*pixels;
// 	int32_t *img_px;
// 	//float	text_y;
// 	//float	text_y_step;

// 	//text_y = 0;
	
// 	i = 0;
// 	load_textures(game);
// 	printf("width of south texture:%u\n", game->textures->south_t->width);
// 	printf("height of south texture:%u\n", game->textures->south_t->height);
// 	pixels = game->textures->south_t->pixels;
// 	img_px = (int32_t *)pixels;
// 	while (i < 10)
// 	{
// 		printf("pixels of south texture:%d\n", img_px[i]);
// 		i++;
// 	}
// }

void	draw_col(t_game *game)
{
	int	col_x;
	int	wall_start;
	int wall_end;
	int y;

	y = 0;
	col_x = game->render->ray;
	if (col_x >= WIDTH)
		return ;
	
	wall_start = (HEIGHT / 2) - (game->render->line_height / 2);
	wall_end = (HEIGHT / 2) + (game->render->line_height / 2);
	while (y < HEIGHT)
	{
		if (y < wall_start) // ceiing
			 mlx_put_pixel(game->render->ray_image, col_x, y, game->colors->c_rgb);
		else if (y > wall_end) // floor
			mlx_put_pixel(game->render->ray_image, col_x, y,  game->colors->f_rgb);
		else
		{
			//put_textures( game, wall_start, wall_end, col_x , y);
			mlx_put_pixel(game->render->ray_image, col_x, y, WALL);
		}
		y++;
	}
}