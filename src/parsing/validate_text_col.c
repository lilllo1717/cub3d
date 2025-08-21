/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_text_col.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:36:51 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/20 14:39:25 by tignatov         ###   ########.fr       */
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

static int	ft_count_substrings(const char *s, char c)
{
	int	i;
	int	count;
	int	in_substring;

	i = 0;
	count = 0;
	in_substring = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && !in_substring)
		{
			in_substring = 1;
			count++;
		}
		else if (s[i] == c)
			in_substring = 0;
		i++;
	}
	return (count);
}

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

bool	is_valid_text(char *line)
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

bool	is_valid_color(char *line)
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

int	parse_file(char **file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (is_texture(file[i]) && !is_valid_text(file[i]))
			return (false);
		if (is_color(file[i]) && !is_valid_color(file[i]))
			return (false);
		i++;
	}
	return (true);
}
