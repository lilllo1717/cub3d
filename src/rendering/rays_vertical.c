/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:00:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/23 11:24:02 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************************************
 * 
 *	-function that calculates the initial intersection and step offsets
 * for vertical raycasting based on the player's angle.
 *	-it determines where a vertical ray first intersects a grid line
 * and how much to step in the x and y directions for each subsequent check,
 * depending on where the player is looking at
 * 	-it prepares the ray's starting position and increments for vertical wall
 * detection in a 2d grid map
 * 
 * game->render->ray_angle < P2 || game->render->ray_angle > P3 - looking right
 * game->render->ray_angle > P2 && game->render->ray_angle < P3 - looking left
 * 
 * 	x_o and y_o = x and y offset, determine how much the ray should move
 * horizontally and vertically each time the ray advances to the next vertical
 * grid line
 * 
******************************************************************************/
static void	setup_vertical_rays(t_game *game, int max_dof)
{
	(void)max_dof;
	if (game->render->ray_angle > P2 && game->render->ray_angle < P3)
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE)
			- 0.001;
		game->render->ray_y = game->render->player_y + (game->render->ray_x
				- game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_o = -TILE;
		game->render->y_o = game->render->x_o
			* tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle < P2 || game->render->ray_angle > P3)
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE)
			+ TILE;
		game->render->ray_y = game->render->player_y + (game->render->ray_x
				- game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_o = TILE;
		game->render->y_o = game->render->x_o * tan(game->render->ray_angle);
	}
}

/******************************************************************************
 *
 *	-function checks for a vertical wall hit in the map during raycasting
 *	-it updates ray position, wall direction, and distance if a wall is hit
 * 	-otherwise, advances the ray to the next vertical grid intersection.
 * 
 * 	-game->render->ray_angle > P2 && game->render->ray_angle < P3) this means 
 * the ray is pointing left or WEST
 *
 *****************************************************************************/
static void	vert_wall_hit(t_game *game, int max_dof)
{
	if (game->map[game->render->m_y][game->render->m_x] == '1')
	{
		game->render->vertical_ray_x_pos = game->render->ray_x;
		game->render->vertical_ray_y_pos = game->render->ray_y;
		game->render->v_distance = distance(game->render->player_x,
				game->render->player_y,
				game->render->vertical_ray_x_pos,
				game->render->vertical_ray_y_pos);
		if (game->render->ray_angle > P2
			&& game->render->ray_angle < P3)
			game->render->wall_dir = WEST;
		else
			game->render->wall_dir = EAST;
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
 * 	-function detects vertical wall collisions for the current ray in 
 * the game
 *	-updates the rendering state with wall hit information or stops 
 * if out of bounds
 *
 *****************************************************************************/
static void	vertical_wall_detection(t_game *game, int max_dof)
{
	while (game->render->dof < max_dof)
	{
		game->render->m_x = (int)(game->render->ray_x) / TILE;
		game->render->m_y = (int)(game->render->ray_y) / TILE;
		if (game->render->m_x >= 0
			&& game->render->m_x < (int)game->map_info.max_len
			&& game->render->m_y >= 0
			&& game->render->m_y < (int)game->map_info.num_rows)
			vert_wall_hit(game, max_dof);
		else
			game->render->dof = max_dof;
	}
}

/******************************************************************************
 * 
 * 	-function that checks for vertical wall intersections by casting rays 
 * from the player's position
 *	-sets up the initial ray positions and detects where the rays hit 
 * vertical walls
 * 	-max_dof = maximum number of grind intersecctions we take until we 
 * give up looking for a wall hit
 * 
******************************************************************************/
void	check_vertical_lines(t_game *game)
{
	int	max_dof;

	max_dof = game->map_info.max_len;
	game->render->vertical_ray_x_pos = game->render->player_x;
	game->render->vertical_ray_y_pos = game->render->player_y;
	setup_vertical_rays(game, max_dof);
	vertical_wall_detection(game, max_dof);
}
