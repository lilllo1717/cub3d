#include "cub3d.h"

void	setup_vertical_rays(t_game *game, int max_dof)
{
	if (game->render->ray_angle > P2 && game->render->ray_angle < P3) // looking left
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE)
			- 0.001;
		game->render->ray_y = game->render->player_y + (game->render->ray_x
				- game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_offset = -TILE;
		game->render->y_offset = game->render->x_offset
			* tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle < P2 || game->render->ray_angle > P3)		// looking right
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE)
			+ TILE;
		game->render->ray_y = game->render->player_y + (game->render->ray_x
				- game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_offset = TILE;
		game->render->y_offset = game->render->x_offset
			* tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle == P2 || game->render->ray_angle == P3) // looking straight up or down
	{
		game->render->ray_x = game->render->player_x;
		game->render->ray_y = game->render->player_y;
		game->render->dof = max_dof;
	}
}

void	check_vertical_lines(t_game *game)
{
	int	max_dof;

	// if (game->map_info.max_len > game->map_info.num_rows)
	max_dof = game->map_info.max_len;
	// else
	// 	max_dof = game->map_info.num_rows;
	game->render->vertical_ray_x_pos = game->render->player_x;
	game->render->vertical_ray_y_pos = game->render->player_y;
	setup_vertical_rays(game, max_dof);
	vertical_wall_detection(game, max_dof);
}

void	vertical_wall_detection(t_game *game, int max_dof)
{
	while (game->render->dof < max_dof)
	{
		game->render->m_x = (int)(game->render->ray_x) / TILE;
		game->render->m_y = (int)(game->render->ray_y) / TILE;
		if (game->render->m_x >= 0
			&& game->render->m_x < (int)game->map_info.max_len
			&& game->render->m_y >= 0
			&& game->render->m_y < (int)game->map_info.num_rows)
		{
			if (game->map[game->render->m_y][game->render->m_x] == '1')
			{
				game->render->vertical_ray_x_pos = game->render->ray_x;
				game->render->vertical_ray_y_pos = game->render->ray_y;
				game->render->v_distance = distance(game->render->player_x,
						game->render->player_y,
						game->render->vertical_ray_x_pos,
						game->render->vertical_ray_y_pos);
				if (game->render->ray_angle > P2
					&& game->render->ray_angle < P3) // Ray pointing left
					game->render->wall_dir = WEST;
				else
					game->render->wall_dir = EAST;
				game->render->dof = max_dof;
			}
			else //next line
			{
				game->render->ray_x += game->render->x_offset;
				game->render->ray_y += game->render->y_offset;
				game->render->dof += 1;
			}
		}
		else
			game->render->dof = max_dof;
	}
}