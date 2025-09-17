/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:12 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/17 14:39:40 by rojornod         ###   ########.fr       */
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

int	mlx_start(t_game *game)
{
	printf("starting mlx\n");
	game->render->mlx = mlx_init(WIDTH, HEIGHT, "BEST GAME EVER", false);
	if (!game->render->mlx)
	{
		err("Failed to initialize MLX42.\n");
		return (0);
	}
	else
		printf("mlx started\n");
	mlx_key_hook(game->render->mlx, &key_handler, game->render);
	create_world(game);
	return (1);
}

void	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_rays(game);
	draw_player(game);
	left_right(game);
	forward_backward(game);
	turn(game);
}
