/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:04:28 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/22 12:17:50 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_pos(t_game *game, float x, float y)
{
    int col = (int)(x / TILE);
    int row = (int)(y / TILE);

    if ( row >= 0 && row < (int)game->map_info.num_rows 
    	&& col >= 0 && col < (int)game->map_info.max_len 
    	&& game->map[row][col] != '1')
		return (1);
	else 
		return (0);
}

static void	update_pos(t_game *game, float next_pos_x, float next_pos_y)
{
	int	col;
	int	row;

	col = (int)(next_pos_x / TILE);
	row = (int)(next_pos_y / TILE);
	if (check_pos(game, next_pos_x - (TILE / 3), next_pos_y - (TILE / 3)) //top left
       	&& check_pos(game, next_pos_x + (TILE / 3), next_pos_y - (TILE / 3)) //top right
    	&& check_pos(game, next_pos_x - (TILE / 3), next_pos_y + (TILE / 3)) //bottom left
    	&& check_pos(game, next_pos_x + (TILE / 3), next_pos_y + (TILE / 3))) //bottom right
	{
		game->render->player_x = next_pos_x;
		game->render->player_y = next_pos_y;
	}
}

void	left_right(t_game *game)
{
	float	next_pos_x;
	float	next_pos_y;

	next_pos_x = game->render->player_x;
	next_pos_y = game->render->player_y;
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_A))
	{
		next_pos_x += game->render->player_delta_y
			* game->render->mlx->delta_time;
		next_pos_y += -game->render->player_delta_x
			* game->render->mlx->delta_time;
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_D))
	{
		next_pos_x += -game->render->player_delta_y
			* game->render->mlx->delta_time;
		next_pos_y += game->render->player_delta_x
			* game->render->mlx->delta_time;
	}
	update_pos(game, next_pos_x, next_pos_y);
}

void	forward_backward(t_game *game)
{
	float	next_pos_x;
	float	next_pos_y;

	next_pos_x = game->render->player_x;
	next_pos_y = game->render->player_y;
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_W))
	{
		next_pos_x += game->render->player_delta_x
			* game->render->mlx->delta_time;
		next_pos_y += game->render->player_delta_y
			* game->render->mlx->delta_time;
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_S))
	{
		next_pos_x -= game->render->player_delta_x
			* game->render->mlx->delta_time;
		next_pos_y -= game->render->player_delta_y
			* game->render->mlx->delta_time;
	}
	update_pos(game, next_pos_x, next_pos_y);
}

void	turn(t_game *game)
{
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_RIGHT))
	{
		game->render->player_angle += 2.5 * game->render->mlx->delta_time;
		if (game->render->player_angle > 2.0 * PI)
			game->render->player_angle -= 2.0 * PI;
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_LEFT))
	{
		game->render->player_angle -= 2.5 * game->render->mlx->delta_time;
		if (game->render->player_angle < 0.0)
			game->render->player_angle += 2.0 * PI;
	}
	game->render->player_delta_x = cos(game->render->player_angle) * M_SPEED;
	game->render->player_delta_y = sin(game->render->player_angle) * M_SPEED;
}

/*
			* Callback function used to handle raw mouse movement.
 *
 * @param[in] xpos The mouse x position.
 * @param[in] ypos The mouse y position.
 * @param[in] param Additional parameter to pass on to the function.

	typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);
 */

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	mouse_delta;

	(void)ypos;
	game = (t_game *)param;
	mlx_set_cursor_mode(game->render->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->render->mlx, WIDTH / 2, HEIGHT / 2);
	mouse_delta = (xpos - WIDTH / 2) * 0.009 * game->render->mlx->delta_time;
	game->render->player_angle += mouse_delta;
	game->render->player_delta_x = cos(game->render->player_angle) * 5.0;
	game->render->player_delta_y = sin(game->render->player_angle) * 5.0;
}
