/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:57:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/23 11:23:57 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************************************
 * 
 * 	-function initializes the distances and direction for the current ray by:
 * |setting large default distances for horizontal and vertical wall hits
 * |normalizing the ray angle
 * |checking for horizontal and vertical wall intersections
 * |storing the direction of the closest horizontal and vertical walls
 * 
******************************************************************************/
static void	initial_ray_calc(t_game *game)
{
	game->render->h_distance = 9999999;
	game->render->v_distance = 9999999;
	game->render->dof = 0;
	normalize_angle(game);
	game->render->dof = 0;
	check_horizontal_lines(game);
	game->render->wall_dir_h = game->render->wall_dir;
	game->render->dof = 0;
	check_vertical_lines(game);
	game->render->wall_dir_v = game->render->wall_dir;
}

/******************************************************************************
 * 
 *	-function chooses the closest intersection (vertical or horizontal) 
 * for the current ray and updates the render state accordingly
 *	-it compares the distances to the nearest vertical and horizontal walls
 * and chooses the smallest one, so the one closer to the player
 * 
******************************************************************************/
static void	select_closest_intersec(t_game *game)
{
	if (game->render->v_distance < game->render->h_distance)
	{
		game->render->ray_x = game->render->vertical_ray_x_pos;
		game->render->ray_y = game->render->vertical_ray_y_pos;
		game->render->final_dist = game->render->v_distance;
		game->render->wall_hit_x = game->render->vertical_ray_x_pos;
		game->render->wall_hit_y = game->render->vertical_ray_y_pos;
		game->render->wall_dir = game->render->wall_dir_v;
	}
	if (game->render->h_distance < game->render->v_distance)
	{
		game->render->ray_x = game->render->horizontal_ray_x_pos;
		game->render->ray_y = game->render->horizontal_ray_y_pos;
		game->render->final_dist = game->render->h_distance;
		game->render->wall_hit_x = game->render->horizontal_ray_x_pos;
		game->render->wall_hit_y = game->render->horizontal_ray_y_pos;
		game->render->wall_dir = game->render->wall_dir_h;
	}
}

/******************************************************************************
 *
 *	-function starts by calculating the corrected distance to the wall for the
* current ray. this is to avoid fish-eye distortion.
 *	-it determines the height and vertical offset of the wall slice to draw 
 * and renders the column
 * -updates the ray angle for thex next column
 *
 *****************************************************************************/
static void	render_ray_col(t_game *game, float ray_angle_increment)
{
	game->render->correct_distance = game->render->final_dist
		* cos(game->render->ray_angle - game->render->player_angle);
	if (game->render->correct_distance < 1.0)
		game->render->correct_distance = 1.0;
	game->render->line_height = (64 * HEIGHT) / game->render->correct_distance;
	if (game->render->line_height < 1)
		game->render->line_height = 1;
	game->render->line_offset = (HEIGHT / 2) - (game->render->line_height / 2);
	draw_col(game);
	game->render->ray++;
	game->render->ray_angle += ray_angle_increment;
}

/******************************************************************************
 * 
 *	-function that casts and draws all rays for the current frame in the 
 * raycasting renderer.
 *	-it initializes the raycasting parameters, clears the ray image buffer,
 * iterates over each vertical column casting a ray and rendering the result
 * 	-its called once per frame to keep the rendering accurate
 *
 * ray_angle_increment = the ammount the ray angle increases for each column of
 * the screen. it is the fov divided by the screen width so each ray gets 
 * spaced out evenly
 * 
 * fov = PI / 3 this means the field of view of the player is 60 degrees
 * 
 * ray_angle_increment = game->render->fov / WIDTH; this means the increment
 * will be roughly 0.0312 degrees per ray
 * 
 ******************************************************************************/
void	cast_rays(void *param)
{
	float		ray_angle_increment;
	t_game		*game;

	game = (t_game *)param;
	if (!game || !game->render->ray_image || !game->render->ray_image->pixels)
		return ;
	ft_memset(game->render->ray_image->pixels, 0, WIDTH * HEIGHT
		* sizeof(int32_t));
	game->render->fov = PI / 3;
	ray_angle_increment = game->render->fov / WIDTH;
	game->render->ray_angle = game->render->player_angle
		- (game->render->fov / 2);
	normalize_angle(game);
	game->render->ray = 0;
	while (game->render->ray < WIDTH)
	{
		initial_ray_calc(game);
		select_closest_intersec(game);
		render_ray_col(game, ray_angle_increment);
	}
}
