/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:58:39 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/19 14:32:52 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int argc, char **argv)
{
    t_game  	game;
	t_render	*render;
	
    printf("Hello!");
    if (is_valid_input(argc, argv) == false)
		return (1);
    parse_map(&game, argv[1]);
	render = init_render();
	mlx_start(render);
	mlx_key_hook(render->mlx, &key_handler, render);
	mlx_loop_hook(render->mlx, &draw_player, render);
	mlx_loop(render->mlx);
	mlx_terminate(render->mlx);
	free(render); //needs to be freed somewhere else
}  