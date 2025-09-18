/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:15:46 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 14:16:17 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_col_tex(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (true);
	return (false);
}

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
	err("Invalid input present.\n");
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
		if (map[i + 1] && ft_strchr(map[i], '1') && ft_strchr(map[i + 1], '1')
			&& !is_col_tex(map[i]))
			found = 1;
		if (no_invalid_input(map[i], found) == false)
			return (false);
		else if (found == 1 && map[i + 1] && ft_strchr(map[i], '1')
			&& !ft_strchr(map[i + 1], '1'))
			found = 2;
		else if (found == 2 && map[i][0] != '\n')
			return (err("Invalid input: map is not last.\n"), false);
		i++;
	}
	return (true);
}
