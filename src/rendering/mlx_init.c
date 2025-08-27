/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:12 by rojornod          #+#    #+#             */
/*   Updated: 2025/08/27 15:31:34 by rojornod         ###   ########.fr       */
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
	render->map = malloc(sizeof(int) * 25 * 14);
	if (!render->map)
	{
		free(render);
		return (NULL);
	}
	render->h_distance = 1000000;
	render->v_distance = 1000000;
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
	{
		render->player_x += render->player_delta_x;
		render->player_y += render->player_delta_y;
	}
	if (mlx_is_key_down(render->mlx, MLX_KEY_S))
	{
		render->player_x -= render->player_delta_x;
		render->player_y -= render->player_delta_y;
	}
	if (mlx_is_key_down(render->mlx, MLX_KEY_D))
	{
		render->player_angle += 0.1;
		if (render->player_angle > render->player_angle > 2 * PI)
			render->player_angle -= 2 * PI;
		render->player_delta_x = cos(render->player_angle) * 5;
		render->player_delta_y = sin(render->player_angle) * 5;
	}
	if (mlx_is_key_down(render->mlx, MLX_KEY_A))
	{
		render->player_angle -= 0.1;
		if (render->player_angle < 0)
			render->player_angle += 2 * PI;
		render->player_delta_x = cos(render->player_angle) * 5;
		render->player_delta_y = sin(render->player_angle) * 5;
	}
	draw_rays(render);
	draw_player(render);
}

/*
	The deltas tell us wich direction the line goes, how steep the line is, how many steps are needed to draw the complete line
and which axis to use as the primary stepping direction (larger absoulte delta).
	float delta_x : horizontal distance form start to end
					if negative line goes right, if postive line goes left, if 0 just a vertical line
	float delta_y : vertical distance form start to end
					if positive line goes down, if negative line goes up, if 0 just a horizontal line
*/
// void	draw_line(mlx_image_t *img, float start_y, float start_x, float end_y,
// 	float end_x)
// {
// 	float	delta_x;
// 	float	delta_y;
	
// 	delta_x = end_x - start_x;
// 	delta_y = end_y - start_y;
	
// 	while ()
// 	{
		
// 	}
// }


