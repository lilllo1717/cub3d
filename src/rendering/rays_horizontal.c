#include "cub3d.h"

void	check_horizontal_lines(t_game *game)
{
	int	max_dof;

	// if (game->map_info.max_len > game->map_info.num_rows)
	// 	max_dof = game->map_info.max_len;
	// else
	max_dof = game->map_info.num_rows;
	game->render->horizontal_ray_x_pos = game->render->player_x;
	game->render->horizontal_ray_y_pos = game->render->player_y;
	setup_horizontal_rays(game, max_dof);
	horizontal_wall_detection(game, max_dof);
}

void	setup_horizontal_rays(t_game *game, int max_dof)
{
	if (game->render->ray_angle > PI) // looking up
	{
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE)
			- 0.001;
		game->render->ray_x = game->render->player_x + (game->render->ray_y
				- game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_offset = -TILE;
		game->render->x_offset = game->render->y_offset
			/ tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle < PI) // looking down
	{
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE)
			+ TILE;
		game->render->ray_x = game->render->player_x + (game->render->ray_y
				- game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_offset = TILE;
		game->render->x_offset = game->render->y_offset
			/ tan(game->render->ray_angle);
	}
	else if (game->render->ray_angle == 0 || game->render->ray_angle == PI) // looking straight left or right
	{
		game->render->ray_x = game->render->player_x;
		game->render->ray_y = game->render->player_y;
		game->render->dof = max_dof;
	}
}

void	horizontal_wall_detection(t_game *game, int max_dof)
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
				game->render->horizontal_ray_x_pos = game->render->ray_x;
				game->render->horizontal_ray_y_pos = game->render->ray_y;
				if (game->render->ray_angle > PI)
					game->render->wall_dir = NORTH;
				else
					game->render->wall_dir = SOUTH;
				game->render->h_distance = distance(game->render->player_x,
						game->render->player_y,
						game->render->horizontal_ray_x_pos,
						game->render->horizontal_ray_y_pos);
				game->render->dof = max_dof;
			}
			else
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

