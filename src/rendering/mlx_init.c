/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:12 by rojornod          #+#    #+#             */
/*   Updated: 2025/08/22 14:33:05 by rojornod         ###   ########.fr       */
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

void	mlx_start(t_render *render)
{
	render->mlx = mlx_init(WIDTH, HEIGHT, "BEST GAME EVER", true);
	if (!render->mlx)
	{
		perror("Failed to initialize MLX42");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(render->mlx, &key_handler, render);
	create_world(render);
	draw_player(render);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_render	*render;

	render = (t_render *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_putendl_fd("Goodbye", 1);
		mlx_close_window(render->mlx);
	}
	if (mlx_is_key_down(render->mlx, MLX_KEY_W))
		render->player_y -= MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_S))
		render->player_y += MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_D))
		render->player_x += MOVEMENT;
	if (mlx_is_key_down(render->mlx, MLX_KEY_A))
		render->player_x -= MOVEMENT;
	draw_player(render);
}


