/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:17:46 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 10:00:50 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2darray_partial(char **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2dint_partial(int **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2dint(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_render(t_render *render)
{
	// free_2dint(&render->map);
	if (render->player_image)
		mlx_delete_image(render->mlx, render->player_image);
	if (render->ray_image)
		mlx_delete_image(render->mlx, render->ray_image);
	if (render->mlx)
		mlx_terminate(render->mlx);
	free(render);
}

void	free_game(t_game *game)
{
	free_2darray(game->initial_file);
	free_2darray(game->map);
	free(game->colors);
	free(game->textures->n_text);
	free(game->textures->s_text);
	free(game->textures->w_text);
	free(game->textures->e_text);
	// mlx_delete_image(game->render->mlx, game->textures->east_t);
	// mlx_delete_image(game->render->mlx, game->textures->west_t);
	// mlx_delete_image(game->render->mlx, game->textures->south_t);
	// mlx_delete_image(game->render->mlx, game->textures->north_t);
	if (game->textures->east_t)
		mlx_delete_texture(game->textures->east_t);
	if (game->textures->west_t)
		mlx_delete_texture(game->textures->west_t);
	if (game->textures->south_t)
		mlx_delete_texture(game->textures->south_t);
	if (game->textures->north_t)
		mlx_delete_texture(game->textures->north_t);
	free(game->textures);
	free_render(game->render);
	game = NULL;
}
