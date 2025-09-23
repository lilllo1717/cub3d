/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:31:04 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/22 15:55:57 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************************************
*	-function that checks if the coordinates given are within the map and 
* not inside a wall
*	-returns 1 if valid and 0 if not valid
******************************************************************************/
static int	check_pos(t_game *game, float x, float y)
{
	int	col;
	int	row;

	col = (int)(x / TILE);
	row = (int)(y / TILE);
	if (row >= 0 && row < (int)game->map_info.num_rows && col >= 0
		&& col < (int)game->map_info.max_len && game->map[row][col] != '1')
		return (1);
	else
		return (0);
}

/******************************************************************************
 *	-function updates the position of the player after checking if 
 * all the corners around the player are in valid coordinates on the map
 * 	-*TILE / 3* bounding box around the player with the size smaller
 * than the tile size
 * 
 *	game, next_pos_x - (TILE / 3), next_pos_y - (TILE / 3))* top left
 *	game, next_pos_x + (TILE / 3), next_pos_y - (TILE / 3))* top right
 *	game, next_pos_x - (TILE / 3), next_pos_y + (TILE / 3))* bottom left
 *	game, next_pos_x + (TILE / 3), next_pos_y + (TILE / 3)))* bottom right
 *		
*******************************************************************************/
void	update_pos(t_game *game, float next_pos_x, float next_pos_y)
{
	int	col;
	int	row;

	col = (int)(next_pos_x / TILE);
	row = (int)(next_pos_y / TILE);
	if (check_pos(game, next_pos_x - (TILE / 3), next_pos_y - (TILE / 3))
		&& check_pos(game, next_pos_x + (TILE / 3), next_pos_y - (TILE / 3))
		&& check_pos(game, next_pos_x - (TILE / 3), next_pos_y + (TILE / 3))
		&& check_pos(game, next_pos_x + (TILE / 3), next_pos_y + (TILE / 3)))
	{
		game->render->player_x = next_pos_x;
		game->render->player_y = next_pos_y;
	}
}
