/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:53:21 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/20 14:41:57 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2darray_partial(char **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2darray(char **arr)
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

int	count_num_lines(char *file)
{
	int	num_lines;
	int	fd;

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

int	ft_count_substrings(const char *s, char c)
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

