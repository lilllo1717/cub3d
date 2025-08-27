/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_outer_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:02:45 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/27 12:20:36 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_dfs(char **map, size_t row, size_t col, t_map *map_dim)
{
	if (row < 0 || row >= map_dim->num_rows + 2 || col < 0
		|| col >= map_dim->max_len + 2)
		return (0);
	if (map[row][col] == '1')
		return (0);
	if (map[row][col] != ' ')
		return (1);
	map[row][col] = '1';
	if (ft_dfs(map, row - 1, col, map_dim))
		return (1);
	if (ft_dfs(map, row + 1, col, map_dim))
		return (1);
	if (ft_dfs(map, row, col + 1, map_dim))
		return (1);
	if (ft_dfs(map, row, col - 1, map_dim))
		return (1);
	return (0);
}

int	validate_map(char **initial_file)
{
	t_map	map;
	char	**map_to_valid;

	map = find_map_size(initial_file);
	map_to_valid = map_for_valid(initial_file, &map);
	print_2d_array(map_to_valid);
	if (ft_dfs(map_to_valid, 0, 0, &map)
		|| map_chars_valid(map_to_valid) == false)
	{
		free_2darray(map_to_valid);
		printf("Map is invalid.\n");
	}
	else
		printf("Map is valid.\n");
	return (1);
}
