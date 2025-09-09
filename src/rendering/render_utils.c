#include "cub3d.h"

void	normalize_angle(t_game *game)
{
	if (game->render->ray_angle < 0)
		game->render->ray_angle += 2 * PI;
	else if (game->render->ray_angle > 2 * PI)
		game->render->ray_angle -= 2 * PI;
}

int	load_textures(t_game *game)
{
	game->textures->east_t = mlx_load_png(game->textures->e_text);
	game->textures->west_t = mlx_load_png(game->textures->w_text);
	game->textures->south_t = mlx_load_png(game->textures->s_text);
	game->textures->north_t = mlx_load_png(game->textures->n_text);
	if (!game->textures->east_t || !game->textures->west_t 
			|| !game->textures->south_t || !game->textures->north_t)
	{
		printf("Error\nFailure to load textures\n");
		return (1);
	}
	return (0);
}
