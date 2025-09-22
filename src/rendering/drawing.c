/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:20:51 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/22 17:14:31 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	draw_line(t_render *render, int begin_x,
//					int begin_y, int end_x, int end_y)
// {
// 	// float	delta_x;
// 	// float	delta_y;
// 	// float	current_x;
// 	// float	current_y;
// 	// float	step_x;
// 	// float	step_y;
// 	// int		steps;
// 	int		i;

// 	i = 0;
// 	// deltas are the total horizontal and vertical distance from
//	//start point to end point.
// 	//		positive delta y - line goes down
// 	//		negative delta y - line goes up
// 	// 		0 - horizontal line
// 	render->line->delta_y = render->line->end_y - render->line->begin_y;

// 	//		positive delta x - line goes right
// 	//		negative delta x - line goes left
// 	// 		0 - vertical line
// 	render->line->delta_x = render->line->end_x - render->line->begin_x;
//
// 	render->line->steps = determine_steps(render->line->delta_x,
//	render->line->delta_y);
//
// 	// steps calculate the incremental step sizes needed to draw a
//	//consistent line between 2 points
// 	render->line->step_x = render->line->delta_x / render->line->steps;
// 	render->line->step_y = render->line->delta_y / render->line->steps;
// 	//current initializes the starting position for the line drawing
//  //by setting the current drawing coordinates to
//	//the beggining of the point line
// 	render->line->current_x = render->line->begin_x;
// 	render->line->current_y = render->line->begin_y;
//
// 	we put pixels until we have as many as the steps calculated before,
// 	we use the current variables to have the starting position of the ray
// 	while (i <= render->line->steps)
// 	{
// 		//only drawing rays on right half of the window
// 		if ((int)render->line->current_x >= 0
//				&& (int)render->line->current_x < WIDTH &&
// 				(int)render->line->current_y >= 0
//				&& (int)render->line->current_y < HEIGHT)
// 			mlx_put_pixel(render->ray_image, (int)render->line->current_x,
//	(int)render->line->current_y, 0xFF0000FF);
// 		render->line->current_x += render->line->step_x;
// 		render->line->current_y += render->line->step_y;
// 		i++;
// 	}
// 	// printf("[%f]\n", render->ray_angle);

// 	return (0);
// }

/******************************************************************************
*	black for invalid coordinates
*	return (0x000000);
*	***************************************************************************
*	this calculates the pixel position in the texture data
*	pixel = &texture->pixels[(y * texture->width + x)
*		* texture->bytes_per_pixel];
*	***************************************************************************
*	this combines the rgba values into a single uint32_t
*	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
******************************************************************************/
static uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	uint8_t		*pixel;
	uint32_t	color;

	if (!texture || x < 0 || y < 0 || x >= (int)texture->width
		|| y >= (int)texture->height)
		return (0x000000);
	pixel = &texture->pixels[(y * texture->width + x)
		* texture->bytes_per_pixel];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}

/******************************************************************************
*	-the last else calculates texture y offset coordinate relative to wall start
*
*	-this means the pixel is part of the ceiling
*		if (y < draw.wall_start)
*	-this means the pixel is part of the floor
*		else if (y >= draw.wall_end)
*******************************************************************************
*/
static void	draw_col_putpixel_loop(t_draw draw, t_game *game, int y)
{
	while (y < HEIGHT)
	{
		if (y < draw.wall_start)
			mlx_put_pixel(game->render->ray_image, game->render->ray, y,
				game->colors->c_rgb);
		else if (y >= draw.wall_end)
			mlx_put_pixel(game->render->ray_image, game->render->ray, y,
				game->colors->f_rgb);
		else
		{
			draw.tex_y_offset = (y - draw.wall_start) * draw.tex_step;
			draw.tex_y = (int)draw.tex_y_offset;
			if (draw.tex_y < 0)
				draw.tex_y = 0;
			if (draw.tex_y >= (int)draw.wall_t->height)
				draw.tex_y = draw.wall_t->height - 1;
			draw.pixel_color = get_texture_pixel(draw.wall_t, draw.tex_x,
					draw.tex_y);
			mlx_put_pixel(game->render->ray_image, game->render->ray, y,
				draw.pixel_color);
		}
		y++;
	}
}

/******************************************************************************
 *
 *  -function draws a vertical column of the wall on the screen for the current
 * 	ray, selecting the appropriate texture and applying it to the column
 *
 *****************************************************************************/
void	draw_col(t_game *game)
{
	int		y;
	t_draw	draw;

	draw.wall_t = select_correct_texture(game);
	draw.tex_x = (int)get_xcoord_from_texture(game);
	draw.tex_step = (float)draw.wall_t->height
		/ (float)game->render->line_height;
	draw.wall_start = (HEIGHT / 2) - (game->render->line_height / 2);
	draw.wall_end = draw.wall_start + game->render->line_height;
	y = 0;
	draw_col_putpixel_loop(draw, game, y);
}

/******************************************************************************
*
*	-function simply selects the current texture based on the direction of 
* where the ray hit the wall 
*
******************************************************************************/
mlx_texture_t	*select_correct_texture(t_game *game)
{
	if (game->render->wall_dir == NORTH)
		return (game->textures->north_t);
	else if (game->render->wall_dir == SOUTH)
		return (game->textures->south_t);
	else if (game->render->wall_dir == EAST)
		return (game->textures->east_t);
	else if (game->render->wall_dir == WEST)
		return (game->textures->west_t);
	else
		return (NULL);
}

/******************************************************************************
 * 
 *	-function that draws the player
 *	-memset clears the image so we get a fresh image every frame
 *	-the player is drawn on instance depth 3 which means its above the map and
 * 3d render
 * 
******************************************************************************/
void	draw_player(void *param)
{
	t_game	*game;
	float	pixel_x;
	float	pixel_y;
	int		player_inst;

	game = (t_game *)param;
	if (!game->render->player_image)
	{
		game->render->player_image = mlx_new_image(game->render->mlx, WIDTH,
				HEIGHT);
		player_inst = mlx_image_to_window(game->render->mlx,
				game->render->player_image, 0, 0);
		mlx_set_instance_depth(game->render->player_image->instances, 3);
	}
	ft_memset(game->render->player_image->pixels, 0, WIDTH * HEIGHT
		* sizeof(int32_t));
	pixel_x = (game->render->player_x / TILE) * MINITILE + 16;
	pixel_y = (game->render->player_y / TILE) * MINITILE + 16;
	put_tile(game->render->player_image, (int)pixel_x - 5, (int)pixel_y - 5,
		PLAYER_COLOR);
}
