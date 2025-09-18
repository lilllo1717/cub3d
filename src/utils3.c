/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:29:46 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 14:00:07 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err(char *str)
{
	printf("Error.\n");
	printf("%s", str);
}

void	free_step2(t_game *game)
{
	free_2darray(game->initial_file);
	free_2darray(game->map);
	free(game->colors);
	free(game->textures->n_text);
	free(game->textures->s_text);
	free(game->textures->w_text);
	free(game->textures->e_text);
	free_render(game->render);
}

void	free_invalid_map(t_game *game)
{
	free_2darray(game->initial_file);
	if (game->map)
		free_2darray(game->map);
}

void	init_map(t_map *map)
{
	map->max_len = 0;
	map->num_rows = 0;
	map->original_len = 0;
	map->start_index = 0;
	map->end_index = 0;
	map->player_letter = '\0';
	map->player_flag = -1;
}
