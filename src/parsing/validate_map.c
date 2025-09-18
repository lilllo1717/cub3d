/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:02:45 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 09:52:00 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(char *line)
{
	int i = 0;

	while (line[i])
	{
		printf("[%c]", line[i]);
		i++;
	}
	printf("\n");
}

size_t	find_start_index(char *line)
{
	size_t	i;
	size_t	col;

	i = 0;
	col = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '1')
			break ;
		col++;
		i++;
	}
	return (col);
}

size_t	find_end_index(char *line)
{
	size_t	i;
	size_t	col;
	size_t	last;

	i = 0;
	col = 0;
	last = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '1')
			last = col;
		col++;
		i++;
	}
	return (last);
}

void	find_map_dim(t_map *map, char **file, size_t i)
{
	size_t	min_index;
	size_t	new_min_index;
	size_t	new_max_index;
	size_t	max_index;
	size_t	k;

	k = i;
	min_index = find_start_index(file[i]);
	while (file[i] && ft_strchr(file[i], '1'))
	{
		new_min_index = find_start_index(file[i]);
		if (new_min_index < min_index)
			min_index = new_min_index;
		i++;
	}
	map->start_index = min_index;
	i = k;
	max_index = 0;
	while (file[i] && ft_strchr(file[i], '1'))
	{
		new_max_index = find_end_index(file[i]);
		if (new_max_index > max_index)
			max_index = new_max_index;
		i++;
	}
	map->end_index = max_index;
	map->max_len = max_index - min_index + 1;
}


t_map	find_map_size(char **file)
{
	t_map	map = {0, 0, 0, 0, 0, '\0', -1};
	size_t		i;
	size_t		k;

	i = 0;
    map.max_len = 0;
    map.num_rows = 0;
	while (file[i] && (is_color(file[i]) || is_texture(file[i])
			|| !(ft_strchr(file[i], '1'))))
		i++;
	k = i;
	map.original_len = ft_strlen(file[i]);
	while (file[i] && ft_strchr(file[i], '1'))
	{
		map.num_rows++;
		i++;
	}
	find_map_dim(&map, file, k);
	return (map);
}

int	malloc_map(char **map, t_map *map_dim)
{
	size_t	i;

	i = 0;
	while (i < (map_dim->num_rows + 2))
	{
		map[i] = (char *)malloc(map_dim->max_len + 2 + 1);
		// printf("%zu\n",map_dim->max_len);
		if (!map[i])
			return (free_2darray_partial(map, i), 0);
		i++;
	}
	map[i] = NULL;
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

void copy_line(char *file_line, char *result_line, t_map *map_dim)
{
    size_t i;
    size_t k = 0;

	i = map_dim->start_index;
	while (file_line[i] == ' ')
	{
		result_line[k] = ' ';
		i++;
		k++;
	}
    result_line[k++] = ' ';
	while (file_line[i] != '\0' && file_line[i] != '\n' && k < map_dim->max_len + 1)
		result_line[k++] = file_line[i++];
	while (k < map_dim->max_len + 1)
		result_line[k++] = ' ';
	result_line[k++] = ' ';
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
	if (!malloc_map(extrac_map, map_dim))
		return (free(extrac_map), NULL);
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
