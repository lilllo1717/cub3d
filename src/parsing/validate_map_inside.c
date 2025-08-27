/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_inside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:00:19 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/27 12:30:22 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	ft_dfs_inside(char **map, size_t row, size_t col, t_map *map_dim)
// {
// 	if (row < 0 || row >= map_dim->num_rows + 2 || col < 0
// 		|| col >= map_dim->max_len + 2)
// 		return (0);
// 	if (map[row][col] == '1')
// 		return (0);
// 	if (map[row][col] != ' ')
// 		return (1);
// 	map[row][col] = '1';
// 	if (ft_dfs(map, row - 1, col, map_dim))
// 		return (1);
// 	if (ft_dfs(map, row + 1, col, map_dim))
// 		return (1);
// 	if (ft_dfs(map, row, col + 1, map_dim))
// 		return (1);
// 	if (ft_dfs(map, row, col - 1, map_dim))
// 		return (1);
// 	return (0);
// }

bool	player_count_valid(int *player_val, int player_flag)
{
	int	i;

	i = 0;
	while (i < 4)
	{
        printf("%i\n", player_val[i]);
		if (player_val[i] != 1 && player_flag == i)
		{
			printf("Invalid input: Wrong number of player.\n");
			return (false);
		}
        else if (player_val[i] != 0 && player_flag != i)
        		{
			printf("Invalid input: Wrong number of player.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	map_chars_valid(char **map)
{
	int player_val[4] = {0};
	int i;
	int j;
    int player_flag;

	i = 0;
    
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'S'
				&& map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ')
				return (printf("Invalid input: invalid chars.\n"), false);
			if (map[i][j] == 'S')
            {
				player_val[KEY_S]++;
                player_flag = 1;
            }
			else if (map[i][j] == 'N')
            {
                player_flag = 0;
				player_val[KEY_N]++;
            }
			else if (map[i][j] == 'W')
            {
                player_flag = 2;
				player_val[KEY_W]++;
            }
			else if (map[i][j] == 'E')
            {
                player_flag = 3;
				player_val[KEY_E]++;
            }
            j++;
		}
        i++;
	}
    if (player_count_valid(player_val, player_flag) == false)
        return (false);
    return (true);
}
