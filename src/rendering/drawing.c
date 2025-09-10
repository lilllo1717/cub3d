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
static uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    uint8_t	*pixel;
    uint32_t color;

    if (!texture || x < 0 || y < 0 || x >= (int)texture->width || y >= (int)texture->height)
        return (0x000000); // Black for invalid coordinates

    // Calculate pixel position in texture data
    pixel = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
    
    // Combine RGBA values into a single uint32_t
    // Assuming RGBA format
    color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
    
    return (color);
}

void	draw_col(t_game *game)
{
	mlx_texture_t	*hit_wall_texture;
	//int				col_x;
	// int				wall_start;
	// int 			wall_end;
	int 			y;
	//int				tex_x_coord;
	float			texture_step;
	float			texture_pos;
	int		tex_x;
    int		tex_y;
	uint32_t pixel_color;


	tex_x = (int)get_xcoord_from_texture(game);
	hit_wall_texture = select_correct_texture(game);
	texture_step = (float)hit_wall_texture->height / game->render->line_height;
	texture_pos = (game->render->line_offset - HEIGHT / 2 + game->render->line_height / 2) * texture_step;
	y = 0;
	// col_x = game->render->ray;
	// if (col_x >= WIDTH)
	// 	return ;
	// wall_start = (HEIGHT / 2) - (game->render->line_height / 2);
	// wall_end = (HEIGHT / 2) + (game->render->line_height / 2);
	while (y < HEIGHT)
	{
		if (y >= game->render->line_offset && y < game->render->line_offset + game->render->line_height)
        {
            // We're in the wall section - draw texture
            tex_y = (int)texture_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)hit_wall_texture->height)
				tex_y = hit_wall_texture->height - 1;
            texture_pos += texture_step;
            
            // Get pixel color from texture
			pixel_color = get_texture_pixel(hit_wall_texture, tex_x, tex_y);
            
            // Set pixel in the image
            mlx_put_pixel(game->render->ray_image, game->render->ray, y, pixel_color);
        }
        else
        {
            // Draw ceiling or floor
            if (y < game->render->line_offset)
                mlx_put_pixel(game->render->ray_image, game->render->ray, y, 0x87CEEBFF); // Sky blue
            else
                mlx_put_pixel(game->render->ray_image, game->render->ray, y, 0x8B4513FF); // Brown floor
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

