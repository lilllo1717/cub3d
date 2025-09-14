/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:58:39 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/25 13:14:09 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_render	*render;

	(void)argc;
	(void)argv;

	render = init_render();
	if (implement_parsing(&game, render, argc, argv) == 0)
		return (free_render(render), 1);
	game.render = render;
	load_textures(&game);
	mlx_start(&game);
	mlx_cursor_hook(render->mlx, &mouse_handler, &game);
	mlx_key_hook(render->mlx, &key_handler, &game);
	mlx_loop_hook(render->mlx, &draw_rays, &game);
	mlx_loop_hook(render->mlx, &draw_player, render);
	mlx_loop(render->mlx);
	// mlx_terminate(render->mlx);
	free_game(&game);
}
