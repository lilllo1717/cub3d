#include "cub3d.h"

static float	wall_offset_calc(t_game *game)
{
	float	wall_offset;

	if (game->render->wall_dir == NORTH)
		wall_offset = fmodf(game->render->wall_hit_x, TILE);
	else if (game->render->wall_dir == SOUTH)
		wall_offset = TILE - fmodf(game->render->wall_hit_x, TILE);
	else if (game->render->wall_dir == EAST)
		wall_offset = fmodf(game->render->wall_hit_y, TILE);
	else
		wall_offset = TILE - fmodf(game->render->wall_hit_y, TILE);
	return (wall_offset);
}

float	get_xcoord_from_texture(t_game *game)
{
	float			wall_offset;
	float			tex_coord;
	mlx_texture_t	*current_text;

	if (game->render->wall_dir == NORTH)
		current_text = game->textures->north_t;
	else if (game->render->wall_dir == SOUTH)
		current_text = game->textures->south_t;
	else if (game->render->wall_dir == EAST)
		current_text = game->textures->east_t;
	else if (game->render->wall_dir == WEST)
		current_text = game->textures->west_t;
	else
		return (0.0f); // fallback
	wall_offset = wall_offset_calc(game);
	tex_coord = wall_offset * current_text->width / TILE;
	if (tex_coord < 0)
		tex_coord = 0;
	if (tex_coord >= current_text->width)
		tex_coord = current_text->width - 1;
	return (tex_coord);
}