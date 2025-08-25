/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:02:45 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/25 17:14:05 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	find_map_size(char **file)
{
	char	*map_start;
	t_map	map;
	size_t	curr_len;
	int		i;

	map = {0, 0};
	i = 0;
	while (file[i] && (is_color(file[i]) || is_texture(file[i])
			|| !(ft_strchr(file[i], '1'))))
		i++;
	while (file[i] && ft_strchr(file[i], '1'))
	{
		curr_len = ft_strlen(map_start);
		if (curr_len > map.max_len)
			map.max_len = curr_len;
		map.num_rows++;
		i++;
	}
	return (map);
}

int	malloc_map(char **map, t_map *map_dim)
{
	size_t	i;

	i = 0;
	while (i < (map_dim->num_rows + 2 + 1))
	{
		map[i] = (char *)malloc(map_dim->max_len + 2 + 1);
		if (!map[i])
			return (free(map), 0);
		i++;
	}
	return (1);
}

void	fill_with_space(char *extrac_map, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		extrac_map[i] = ' ';
		i++;
	}
	extrac_map[i] = '\0';
}

void	copy_line(char *file_line, char *result_line, t_map *map_dim)
{
	int		i;
	size_t	k;

	i = 0;
	k = 0;
	while (file_line[i] != '\0')
	{
		if (k == 0 || k == map_dim->max_len + 2)
		{
			result_line[k] = ' ';
			k++;
		}
		if (file_line[i] == '\n')
			result_line[k] = ' ';
		else
			result_line[k] = file_line[i];
		i++;
		k++;
	}
	while (k < map_dim->max_len + 2)
	{
		result_line[k] = ' ';
		k++;
	}
	result_line[k] = '\0';
}

char	**map_for_valid(char **file, t_map *map_dim)
{
	int		i;
	size_t	k;
	char	**extrac_map;

	i = 0;
	extrac_map = (char **)malloc((map_dim->num_rows + 2 + 1) * sizeof(char *));
	if (!extrac_map)
		return (NULL);
	malloc_map(extrac_map, map_dim);
	fill_with_space(extrac_map[0], map_dim->max_len + 2);
	while (file[i] && (is_color(file[i]) || is_texture(file[i])
			|| !(ft_strchr(file[i], '1'))))
		i++;
	k = 1;
	while (file[i] && ft_strchr(file[i], '1'))
	{
		copy_line(file[i], extrac_map[k], map_dim);
		i++;
		k++;
	}
	fill_with_space(extrac_map[k], map_dim->max_len + 2);
	k++;
	extrac_map[k] = NULL;
	return (extrac_map);
}

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
	if (ft_dfs(map_to_valid, 0, 0, &map))
		printf("Map is invalid.\n");
	else
		printf("Map is valid.\n");
	return (1);
}
