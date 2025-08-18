/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:58:33 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/18 15:50:56 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_num_lines(char *file)
{
	int	num_lines;
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	num_lines = 0;
	while (get_next_line(fd))
		num_lines++;
	close(fd);
	return (num_lines);
}

void	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		i++;
	}
}

int	parse_map(t_game *game, char *file)
{
	char	*line;
	int		fd;
	int		num_lines;
	int		i;

	line = "";
	num_lines = count_num_lines(file);
	game->initial_file = (char **)malloc(sizeof(char *) * (num_lines + 1));
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while (i < num_lines)
	{
		game->initial_file[i] = get_next_line(fd);
		if (!game->initial_file[i]) // plus free
		{
			printf("we broke!\n");
			break;
		}
		i++;
	}
	game->initial_file[i] = NULL;
	print_2d_array(game->initial_file);
	return (1);
}
