/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:23:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/09/23 12:46:37 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_input_file(char *file_name)
{
	int			fd;
	const char	*file_format = ft_strchr(file_name, '.');

	fd = 0;
	if (file_format == NULL)
		return (err("Can't open the file.\n"), false);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		err("Can't open the file.\n");
		return (false);
	}
	if (ft_strncmp(file_format, ".cub", 4) != 0)
		return (close(fd), err("Wrong format.\n"), false);
	close(fd);
	return (true);
}

bool	is_valid_input(int argc, char **argv)
{
	if (argc != 2)
	{
		err("Wrong nuber of arguments.\n");
		return (false);
	}
	if (is_valid_input_file(argv[1]) == false)
		return (false);
	return (true);
}

bool	check_extension(char *start_pars)
{
	start_pars++;
	while (*start_pars && *start_pars != '.')
		start_pars++;
	if (ft_strncmp(start_pars, ".png", 4) != 0)
		return (err("Wrong file extension.\n"), false);
	return (true);
}
