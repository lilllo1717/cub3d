/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:58:33 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/29 13:13:53 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	no_invalid_input(char *line, int in_map)
{
	char	*map_line;

	map_line = ft_strchr(line, '1');
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0
		|| (ft_strncmp(line, " ", 1) == 0 && map_line != NULL)
		|| (ft_strcmp(line, "\n") == 0) || (map_line != NULL && in_map == 1))
		return (true);
	printf("Invalid input present.\n");
	return (false);
}

bool	is_map_last(char **map)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (map[i])
	{
		if (map[i + 1] && ft_strchr(map[i], '1') && ft_strchr(map[i + 1], '1'))
			found = 1;
		if (no_invalid_input(map[i], found) == false)
			return (false);
		else if (found == 1 && map[i + 1] && ft_strchr(map[i], '1')
			&& !ft_strchr(map[i + 1], '1'))
			found = 2;
		else if (found == 2 && map[i][0] != '\n')
			return (printf("Invalid input: map is not last\n"), false);
		i++;
	}
	return (true);
}

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

int	init_game_parsing(t_game *game)
{
	game->colors = NULL;
	game->colors = (t_color *)malloc(sizeof(t_color));
	if (!game->colors)
		return (0);
	game->colors->c_rgb = (unsigned long)0;
	game->colors->f_rgb = (unsigned long)0;
	game->textures = (t_texture *)malloc(sizeof(t_texture));
	if (!game->textures)
		return (free(game->colors), 0);
	game->textures->e_text = NULL;
	game->textures->w_text = NULL;
	game->textures->n_text = NULL;
	game->textures->s_text = NULL;
	return (1);
}
