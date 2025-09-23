/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:00:41 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/23 11:16:57 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************************************
 * 
 *	-function that calculates the initial intersection and step offsets
 * for horizontal raycasting based on the player's angle.
 *	-it determines where a horizontal ray first intersects a grid line
 * and how much to step in the x and y directions for each subsequent check,
 * depending on where the player is looking at
 * -it prepares the ray's starting position and increments for horizontal wall
 * detection in a 2d grid map
 * 
 * game->render->ray_angle < PI - player looking down
 * game->render->ray_angle > PI - player looking up
 * 
 * 	x_o and y_o = x and y offset, determine how much the ray should move
 * horizontally and vertically each time the ray advances to the next 
 * horizontal grid line
 * 
******************************************************************************/
static void	setup_horizontal_rays(t_game *game, int max_dof)
{
	(void)max_dof;
	if (game->render->ray_angle > PI)
	{
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE)
			- 0.001;
		game->render->ray_x = game->render->player_x + (game->render->ray_y
				- game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_o = -TILE;
		game->render->x_o = game->render->y_o
			/ tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle < PI)
	{
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE)
			+ TILE;
		game->render->ray_x = game->render->player_x + (game->render->ray_y
				- game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_o = TILE;
		game->render->x_o = game->render->y_o / tan(game->render->ray_angle);
	}
}

/******************************************************************************
 *
 *	-funciton checks for a horizontal wall hit in the map during raycasting
 *	-it updates ray position, wall direction, and distance if a wall is hit
 * 	-otherwise, advances the ray to the next horizontal grid intersection.
 *
 *****************************************************************************/
static void	horiz_wall_hit(t_game *game, int max_dof)
{
	if (game->map[game->render->m_y][game->render->m_x] == '1')
	{
		game->render->horizontal_ray_x_pos = game->render->ray_x;
		game->render->horizontal_ray_y_pos = game->render->ray_y;
		if (game->render->ray_angle > PI)
			game->render->wall_dir = NORTH;
		else
			game->render->wall_dir = SOUTH;
		game->render->h_distance = distance(game->render->player_x,
				game->render->player_y,
				game->render->horizontal_ray_x_pos,
				game->render->horizontal_ray_y_pos);
		game->render->dof = max_dof;
	}
	else
	{
		game->render->ray_x += game->render->x_o;
		game->render->ray_y += game->render->y_o;
		game->render->dof += 1;
	}
}

/******************************************************************************
 * 	
 * -function detects horizontal wall collisions for the current ray in 
 * the game
 *	-updates the rendering state with wall hit information or stops 
 * if out of bounds
 *
 *****************************************************************************/
static void	horizontal_wall_detection(t_game *game, int max_dof)
{
	while (game->render->dof < max_dof)
	{
		game->render->m_x = (int)(game->render->ray_x) / TILE;
		game->render->m_y = (int)(game->render->ray_y) / TILE;
		if (game->render->m_x >= 0
			&& game->render->m_x < (int)game->map_info.max_len
			&& game->render->m_y >= 0
			&& game->render->m_y < (int)game->map_info.num_rows)
			horiz_wall_hit(game, max_dof);
		else
			game->render->dof = max_dof;
	}
}

/******************************************************************************
 * 
 * 	-function that checks for horizontal wall intersections by casting rays 
 * from the player's position
 *	-sets up the initial ray positions and detects where the rays hit 
 * horizontal walls
 * 	-max_dof = maximum number of grind intersecctions we take until we 
 * give up looking for a wall hit
 * 
******************************************************************************/
void	check_horizontal_lines(t_game *game)
{
	int	max_dof;

	max_dof = game->map_info.num_rows;
	game->render->horizontal_ray_x_pos = game->render->player_x;
	game->render->horizontal_ray_y_pos = game->render->player_y;
	setup_horizontal_rays(game, max_dof);
	horizontal_wall_detection(game, max_dof);
}
