/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:45:09 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/17 14:52:14 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(t_game *game)
{
	if (game->render->ray_angle < 0)
		game->render->ray_angle += 2 * PI;
	else if (game->render->ray_angle > 2 * PI)
		game->render->ray_angle -= 2 * PI;
}

int	load_textures(t_game *game)
{
	game->textures->east_t = mlx_load_png(game->textures->e_text);
	if (!game->textures->east_t)
		return (err("Failure to load textures.\n"), 0);
	game->textures->west_t = mlx_load_png(game->textures->w_text);
	if (!game->textures->west_t)
		return (err("Failure to load textures.\n"),
			mlx_delete_texture(game->textures->east_t), 0);
	game->textures->south_t = mlx_load_png(game->textures->s_text);
	if (!game->textures->west_t)
		return (err("Failure to load textures.\n"),
			mlx_delete_texture(game->textures->east_t),
			mlx_delete_texture(game->textures->west_t), 0);
	game->textures->north_t = mlx_load_png(game->textures->n_text);
	if (!game->textures->north_t)
		return (err("Failure to load textures.\n"),
			mlx_delete_texture(game->textures->east_t),
			mlx_delete_texture(game->textures->west_t),
			mlx_delete_texture(game->textures->south_t), 0);
	return (1);
}

// finds the bigger distance so the line doesn't have 
//	gaps when drawing diagonally. picks whatever delta (axis) is bigger.
int	determine_steps(float delta_x, float delta_y)
{
	if (fabs(delta_x) > fabs(delta_y))
		return ((int)fabs(delta_x));
	else
		return ((int)fabs(delta_y));
}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
