/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:00:38 by rojornod          #+#    #+#             */
/*   Updated: 2025/09/17 16:15:07 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tile_loop(t_game *game, mlx_image_t	*tile)
{
	int			x;
	int			y;
	int			xo;
	int			yo;
	uint32_t	color;

	x = 0;
	y = 0;
	xo = 0;
	yo = 0;
	while (y < (int)game->map_info.num_rows)
	{
		x = 0;
		while (x < (int)game->map_info.max_len)
		{
			if (game->map[y][x] == '1')
				color = WALL;
			else if (game->map[y][x] == '0' || game->map[y][x] == 'N'
				|| game->map[y][x] == 'S'
				|| game->map[y][x] == 'W' || game->map[y][x] == 'E')
				color = FLOOR;
			else
				color = EMPTY;
			xo = x * MINITILE;
			yo = y * MINITILE;
			if (xo < (WIDTH) && yo < HEIGHT)
				put_tile(tile, xo, yo, color);
			x++;
		}
		y++;
	}
}

void	create_world(void *param)
{
	mlx_image_t	*tile;
	t_game		*game;

	game = (t_game *)param;
	tile = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
	if (!tile)
		return ;
	ft_memset(tile->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	tile_loop(game, tile);
	game->render->ray_image = mlx_new_image(game->render->mlx, WIDTH, HEIGHT);
	if (!game->render->ray_image)
		return ;
	mlx_image_to_window(game->render->mlx, game->render->ray_image, 0, 0);
	mlx_set_instance_depth(game->render->ray_image->instances, 0);
	ft_memset(game->render->ray_image->pixels, 0,
		WIDTH * HEIGHT * sizeof(int32_t));
	mlx_image_to_window(game->render->mlx, tile, 16, 16);
	mlx_set_instance_depth(tile->instances, 2);
	game->render->player_delta_x = cos(game->render->player_angle) * 5;
	game->render->player_delta_y = sin(game->render->player_angle) * 5;
}

void	put_tile(mlx_image_t *image, int start_x, int start_y, uint32_t color)
{
	int	x;
	int	y;
	int	size;

	if (color == PLAYER_COLOR)
		size = PLAYER_SIZE;
	else
		size = MINITILE;
	y = start_y + 1;
	x = start_x + 1;
	while (y < start_y + size - 1)
	{
		x = start_x + 1;
		while (x < start_x + size -1)
		{
			if (x >= 0 && x < (int)image->width && y >= 0
				&& y < (int)image->height)
				mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}
