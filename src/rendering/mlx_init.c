/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:12 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/08 15:18:29 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_render	*init_render(void)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	ft_memset(render, 0, sizeof(t_render));

	return (render);
}

void	mlx_start(t_game *game)
{
	printf("starting mlx\n");
	game->render->mlx = mlx_init(WIDTH, HEIGHT, "BEST GAME EVER", true);
	if (!game->render->mlx)
	{
		perror("Failed to initialize MLX42");
		exit(EXIT_FAILURE);
	}
	else
		printf("mlx started\n");
	mlx_key_hook(game->render->mlx, &key_handler, game->render);
	create_world(game);
	draw_player(game->render);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_putendl_fd("Goodbye", 1);
		mlx_close_window(game->render->mlx);
	}
	left_right(game);
	forward_backward(game);
	turn(game);
	//draw_player(game->render);
}

void	left_right(t_game *game)
{	
	
	int		col;
	int		row;
	float 	next_pos_x;
	float	next_pos_y;

	next_pos_x = game->render->player_x;
	next_pos_y = game->render->player_y;
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_A))
	{
		next_pos_x +=  game->render->player_delta_y;
		next_pos_y += -game->render->player_delta_x;
		
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_D))
	{
		next_pos_x += -game->render->player_delta_y;
		next_pos_y += game->render->player_delta_x;
	}
	col = (int)(next_pos_x / TILE);
	row = (int)(next_pos_y / TILE);
	if (row >= 0 && row < (int)game->map_info.num_rows
		&& col >= 0 && col < (int)game->map_info.max_len
		&& game->map[row][col] != '1')
	{
		game->render->player_x = next_pos_x;
		game->render->player_y = next_pos_y;
	}
}

void	forward_backward(t_game *game)
{
	int	col;
	int	row;
	float 	next_pos_x;
	float	next_pos_y;
	
	next_pos_x = game->render->player_x;
	next_pos_y = game->render->player_y;
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_W))
	{
		next_pos_x += game->render->player_delta_x;
		next_pos_y += game->render->player_delta_y;
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_S))
	{
		next_pos_x -= game->render->player_delta_x;
		next_pos_y -= game->render->player_delta_y;
	}
	col = (int)(next_pos_x / TILE);
	row = (int)(next_pos_y / TILE);
	if (row >= 0 && row < (int)game->map_info.num_rows
		&& col >= 0 && col < (int)game->map_info.max_len
		&& game->map[row][col] != '1')
	{
		game->render->player_x = next_pos_x;
		game->render->player_y = next_pos_y;
	}
}

void	turn(t_game *game)
{
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_RIGHT))
	{
		game->render->player_angle += 0.1;
		if (game->render->player_angle > 2.0 * PI)
			game->render->player_angle -= 2.0 * PI;
		
		
		
		// game->render->player_delta_x = cos(game->render->player_angle) * 5.0;
		// game->render->player_delta_y = sin(game->render->player_angle) * 5.0;
	}
	if (mlx_is_key_down(game->render->mlx, MLX_KEY_LEFT))
	{
		game->render->player_angle -= 0.1;
		if (game->render->player_angle < 0.0)
			game->render->player_angle += 2.0 * PI;
		// game->render->player_delta_x = cos(game->render->player_angle) * 5.0;
		// game->render->player_delta_y = sin(game->render->player_angle) * 5.0;
	}
	game->render->player_delta_x = cos(game->render->player_angle) * 5.0;
	game->render->player_delta_y = sin(game->render->player_angle) * 5.0;
}
