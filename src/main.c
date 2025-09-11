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

// void	free_render(t_render *render)
// {
// 	free_2dint(&render->map);
// 	if (render->player_image)
// 		mlx_delete_image(render->mlx, render->player_image);
// 	if (render->ray_image)
// 		mlx_delete_image(render->mlx, render->ray_image);
// 	if (render->mlx)
// 		mlx_terminate(render->mlx);
// 	free(render);
// }

int	main(int argc, char **argv)
{
	t_game		game;
	t_render	*render;

	(void)argc;
	(void)argv;

	render = init_render();
	if (implement_parsing(&game, render, argc, argv) == 0)
		return (1);
	// printf("east: %s\n", game.textures->e_text);
	// printf("west: %s\n", game.textures->w_text);
	// printf("north: %s\n", game.textures->n_text);
	// printf("south: %s\n", game.textures->s_text);

	game.render = render;
	load_textures(&game);
	mlx_start(&game);
	mlx_cursor_hook(render->mlx, &mouse_handler, &game);
	mlx_key_hook(render->mlx, &key_handler, &game);
	mlx_loop_hook(render->mlx, &draw_rays, &game);
	mlx_loop_hook(render->mlx, &draw_player, render);
	mlx_loop(render->mlx);
	mlx_terminate(render->mlx);
	free_game(&game);
	//free_render(render);
}
