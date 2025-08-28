/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:32:38 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/28 16:01:41 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	malloc_copy_texture(t_game *game, char *start_pars, char c)
{
	size_t	len;

	len = ft_strlen(start_pars);
	if (c == 'N')
	{
		game->textures->n_text = (char *)malloc(len * sizeof(char));
		ft_strncpy(game->textures->n_text, start_pars, len - 1);
	}
	else if (c == 'S')
	{
		game->textures->s_text = (char *)malloc(len * sizeof(char));
		ft_strncpy(game->textures->s_text, start_pars, len - 1);
	}
	else if (c == 'E')
	{
		game->textures->e_text = (char *)malloc(len * sizeof(char));
		ft_strncpy(game->textures->e_text, start_pars, len - 1);
	}
	else if (c == 'W')
	{
		game->textures->w_text = (char *)malloc(len * sizeof(char));
		ft_strncpy(game->textures->w_text, start_pars, len - 1);
	}
	return (1);
}

int	parsing_paths(t_game *game, char c)
{
	int		i;
	char	*start_pars;

	i = 0;
	while (game->initial_file[i])
	{
		start_pars = ft_strchr(game->initial_file[i], c);
		if (start_pars != NULL)
			break ;
		i++;
	}
	while (*start_pars && *start_pars != '.')
		start_pars++;
	malloc_copy_texture(game, start_pars, c);
	return (1);
}

int	parse_textures(t_game *game)
{
	game->textures->e_text = NULL;
	game->textures->w_text = NULL;
	game->textures->n_text = NULL;
	game->textures->s_text = NULL;
	parsing_paths(game, 'N');
	parsing_paths(game, 'S');
	parsing_paths(game, 'W');
	parsing_paths(game, 'E');
	printf("%s\n", game->textures->n_text);
	printf("%s\n", game->textures->w_text);
	return (1);
}
