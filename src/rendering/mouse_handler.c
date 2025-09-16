/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:12:41 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/16 16:41:47 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
         * Callback function used to handle raw mouse movement.
 * 
 * @param[in] xpos The mouse x position.
 * @param[in] ypos The mouse y position.
 * @param[in] param Additional parameter to pass on to the function.

    typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);
 */  

 
#include "cub3d.h"

void	mouse_handler(double xpos, double ypos, void* param)
{
	t_game	*game;
    double  mouse_delta;

	(void)ypos;
	game = (t_game *)param;
	mlx_set_cursor_mode(game->render->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->render->mlx, WIDTH/2, HEIGHT/2);
	mouse_delta = (xpos - WIDTH/2) * 0.009 * game->render->mlx->delta_time;
	game->render->player_angle += mouse_delta;
	game->render->player_delta_x = cos(game->render->player_angle) * 5.0;
	game->render->player_delta_y = sin(game->render->player_angle) * 5.0;
	// mlx_set_mouse_pos(game->render->mlx, WIDTH/2, HEIGHT/2);
}

