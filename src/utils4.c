/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:04:56 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/19 14:29:08 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	malloc_map(char **map, t_map *map_dim)
{
	size_t	i;

	i = 0;
	while (i < (map_dim->num_rows + 2))
	{
		map[i] = (char *)malloc(map_dim->max_len + 2 + 1);
		if (!map[i])
			return (free_2darray_partial(map, i), 0);
		i++;
	}
	map[i] = NULL;
	return (1);
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

bool	has_invalid(char c)
{
	if (c != '1' && c != '0' && c != 'S' && c != 'N' && c != 'W' && c != 'E'
			&& c != ' ')
			return (err("Invalid input: invalid chars.\n"), true);
	return (false);
}
