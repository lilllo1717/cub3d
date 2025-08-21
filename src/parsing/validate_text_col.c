/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_text_col.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:36:51 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/21 15:05:00 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	we assume the input blocks to be fine (all colors present, no invalid input)
	- go int line e.g. NO ./path_to_the_north_texture
	- check if there is some garbage after "NO "
	- check path
	- if everyhting is fine parse into the struct
*/

bool	is_texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (true);
	return (false);
}

bool	is_color(char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (true);
	return (false);
}

bool	is_valid_text_line(char *line)
{
	char	*checking_char;
	int		i;
	int		count_members;

	i = 0;
	checking_char = NULL;
	count_members = ft_count_substrings(line, ' ');
	if (count_members != 2)
		return (printf("Wrong input format for textures.\n"), false);
	if (is_texture(line))
		checking_char = line + 3;
	while (checking_char[i] != '\0' && checking_char[i] != '.')
	{
		while (checking_char[i] == ' ')
			i++;
		if (checking_char[i] == '.' && checking_char[i + 1] == '/')
			return (true);
		else
			return (printf("Wrong input format for textures.\n"), false);
	}
	return (true);
}

bool	is_valid_color_line(char *line)
{
	char	*checking_char;
	int		i;
	int		count_members;

	i = 0;
	checking_char = NULL;
	count_members = ft_count_substrings(line, ' ');
	if (count_members != 2)
		return (printf("1.Wrong input format for color.\n"), false);
	if (is_color(line))
		checking_char = line + 2;
	while (checking_char[i] != '\0')
	{
		while (checking_char[i] == ' ')
			i++;
		if (ft_isdigit(checking_char[i]) || checking_char[i] == ',')
			i++;
		else if (checking_char[i] == '\n' && checking_char[i + 1] == '\0')
			return (true);
		else
			return (printf("2.Wrong input format for color.\n"), false);
	}
	return (true);
}

bool	is_valid_text_path(char *line)
{
	char	*checking_char;
	int		fd;
	char	*file_name;
	int		i;

	checking_char = NULL;
	i = 0;
	checking_char = ft_strchr(line, '.');
	file_name = (char *)malloc(ft_strlen(checking_char) * sizeof(char));
	while (checking_char[i] && checking_char[i] != '\n')
	{
		file_name[i] = checking_char[i];
		i++;
	}
	file_name[i] = '\0';
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (free(file_name), printf("Invalid texture path.\n"), close(fd),
			false);
	close(fd);
	free(file_name);
	return (true);
}

bool	color_valid(char **arr)
{
	int		*int_colors;
	int		i;

	i = 0;
	int_colors = malloc(4 * sizeof(int));
	while (arr[i])
	{
		int_colors[i] = ft_atoi(arr[i]);
		if (int_colors[i] < 0 || int_colors[i] > 255)
		{
			free(int_colors);
			return (false);
		}
		i++;
	}
	free(int_colors);
	return (true);
}

bool	is_valid_color(char *file)
{
	char	*checking_char;
	char	*color;
	int		i;
	int		num_colors;
	char	**split_colors;

	checking_char = NULL;
	split_colors = NULL;
	num_colors = 0;
	i = 0;
	while (*file && !ft_isdigit(*file))
		file++;
	checking_char = file;
	color = (char *)malloc(ft_strlen(checking_char) * sizeof(char));
	if (!color)
		return (NULL);
	while (checking_char[i] && checking_char[i] != '\n')
	{
		color[i] = checking_char[i];
		i++;
	}
	color[i] = '\0';
	num_colors = ft_count_substrings(color, ',');
	if (num_colors != 3)
		return(free(color), false);
	split_colors = ft_split(color, ',');
	if (!split_colors)
		return (free(color), NULL);
	if (color_valid(split_colors) == false)
	{
		printf("Invalid color values.\n");
		free(color);
		free(split_colors);
		return (false);
	}
	free(color);
	free_2darray(split_colors);
	return (true);
}

int	parse_file(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (is_texture(file[i]) && (!is_valid_text_line(file[i])
				|| !(is_valid_text_path(file[i]))))
			return (false);
		if (is_color(file[i]) && (!is_valid_color_line(file[i])
				|| !(is_valid_color(file[i]))))
			return (false);
		i++;
	}
	return (true);
}
