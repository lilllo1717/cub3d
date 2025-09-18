/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:53:37 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 14:16:08 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(t_game *game, char *file)
{
	int	fd;
	int	num_lines;
	int	i;

	num_lines = count_num_lines(file);
	game->initial_file = (char **)malloc(sizeof(char *) * (num_lines + 1));
	if (!game->initial_file)
		return (0);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (i < num_lines)
	{
		game->initial_file[i] = get_next_line(fd);
		if (!game->initial_file[i])
			return (free_2darray_partial(game->initial_file, i), close(fd), 0);
		i++;
	}
	game->initial_file[i] = NULL;
	close(fd);
	return (1);
}

void	find_map_dimensions(t_game *game)
{
	size_t	i;
	size_t	j;

	game->map_info.max_len = 0;
	game->map_info.num_rows = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			j++;
		}
		i++;
		game->map_info.max_len = j;
		game->map_info.num_rows = i;
	}
}

void	find_player_angle(t_game *game, t_render *render)
{
	if (game->map_info.player_letter == 'N')
		render->player_angle = 3 * PI / 2;
	else if (game->map_info.player_letter == 'S')
		render->player_angle = PI / 2;
	else if (game->map_info.player_letter == 'W')
		render->player_angle = PI;
	else if (game->map_info.player_letter == 'E')
		render->player_angle = 0;
}

void	parse_player(t_game *game, t_render *render)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == game->map_info.player_letter)
			{
				render->player_y = (float)(i * TILE) + (TILE / 2);
				render->player_x = (float)(j * TILE) + (TILE / 2);
				find_player_angle(game, render);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	implement_parsing(t_game *game, t_render *render, int argc, char **argv)
{
	if (is_valid_input(argc, argv) == false)
		return (0);
	if (!parse_map(game, argv[1]))
		return (0);
	if (is_map_last(game->initial_file) == false)
		return (free_2darray(game->initial_file), 0);
	if (find_textures(game->initial_file) == false)
		return (free_2darray(game->initial_file), 0);
	if (parse_file(game->initial_file) == false)
		return (free_2darray(game->initial_file), 0);
	if (!validate_map(game, game->initial_file, render))
		return (free_invalid_map(game), 0);
	find_map_dimensions(game);
	parse_player(game, render);
	if (!init_game_parsing(game))
		return (free_2darray(game->map), free(game->initial_file), 0);
	if (!parse_colors(game))
		return (free_2darray(game->map), free(game->colors),
			free(game->textures), free(game->initial_file), 0);
	if (!parse_textures(game))
		return (free_2darray(game->map), free(game->colors),
			free(game->textures), free(game->initial_file), 0);
	return (1);
}
