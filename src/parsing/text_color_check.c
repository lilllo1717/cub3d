/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_color_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:21:24 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/18 13:56:01 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	all_color_present(int *color_val)
{
	int	count_color;

	count_color = 0;
	while (count_color < NUM_KEYS2)
	{
		if (color_val[count_color] != 1)
		{
			err("Invalid input: Wrong number of colors.\n");
			return (false);
		}
		count_color++;
	}
	return (true);
}

bool	all_texture_present(int *texture_val)
{
	int	count_text;

	count_text = 0;
	while (count_text < NUM_KEYS1)
	{
		if (texture_val[count_text] != 1)
		{
			err("Invalid input: Wrong number of textures.\n");
			return (false);
		}
		count_text++;
	}
	return (true);
}

void	count_text(char **map, int *texture_val, int *color_val, int i)
{
	if (ft_strncmp(map[i], "NO ", 3) == 0)
		texture_val[KEY_NO]++;
	else if (ft_strncmp(map[i], "SO ", 3) == 0)
		texture_val[KEY_SO]++;
	else if (ft_strncmp(map[i], "WE ", 3) == 0)
		texture_val[KEY_WE]++;
	else if (ft_strncmp(map[i], "EA ", 3) == 0)
		texture_val[KEY_EA]++;
	else if (ft_strncmp(map[i], "C ", 2) == 0)
		color_val[KEY_C]++;
	else if (ft_strncmp(map[i], "F ", 2) == 0)
		color_val[KEY_F]++;
}

int	find_textures(char **map)
{
	int	i;
	int	texture_val[NUM_KEYS1];
	int	color_val[NUM_KEYS2];

	i = 0;
	ft_memset(&texture_val, 0, sizeof(texture_val));
	ft_memset(&color_val, 0, sizeof(color_val));
	while (map[i])
	{
		count_text(map, texture_val, color_val, i);
		i++;
	}
	if (all_color_present(color_val) == false
		|| all_texture_present(texture_val) == false)
		return (false);
	return (true);
}
