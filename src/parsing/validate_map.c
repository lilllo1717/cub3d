/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:02:45 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/27 14:40:35 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	find_map_size(char **file)
{
	char	*map_start;
	t_map	map = {0, 0, '\0'};
	size_t	curr_len;
	int		i;

	i = 0;
    map.max_len = 0;
    map.num_rows = 0;
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
