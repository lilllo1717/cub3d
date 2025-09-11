#include "cub3d.h"

void	check_horizontal_lines(t_game *game, float a_tan)
{
	(void)a_tan;
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
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE) - 0.0001;
		// game->render->ray_x = game->render->player_x + (game->render->player_y - game->render->ray_y)/tan(game->render->ray_angle);
		game->render->ray_x  = game->render->player_x + (game->render->ray_y - game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_offset = -TILE; 
		game->render->x_offset = game->render->y_offset/tan(game->render->ray_angle); 
	}
	else if (game->render->ray_angle < PI) // looking down
	{
		game->render->ray_y = (((int)game->render->player_y / TILE) * TILE) + TILE;
		// game->render->ray_x = game->render->player_x + (game->render->player_y - game->render->ray_y)/ tan(game->render->ray_angle);
		game->render->ray_x  = game->render->player_x + (game->render->ray_y - game->render->player_y) / tan(game->render->ray_angle);
		game->render->y_offset = TILE; 
		game->render->x_offset = game->render->y_offset/tan(game->render->ray_angle);
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
		if (game->render->m_x >= 0 && game->render->m_x < (int)game->map_info.max_len && 
			game->render->m_y >= 0 && game->render->m_y < (int)game->map_info.num_rows)
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
					game->render->player_y, game->render->horizontal_ray_x_pos,
					game->render->horizontal_ray_y_pos, game->render->ray_angle);
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
void	setup_vertical_rays(t_game *game, int max_dof)
{
	if (game->render->ray_angle > P2 && game->render->ray_angle < P3) // looking left
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE) - 0.0001;
		// game->render->ray_y = (game->render->player_x - game->render->ray_x) * tan(game->render->ray_angle) + game->render->player_y;
		game->render->ray_y = game->render->player_y + (game->render->ray_x - game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_offset = -TILE;
		game->render->y_offset = game->render->x_offset * tan(game->render->ray_angle); 
	}
	else if (game->render->ray_angle < P2 || game->render->ray_angle > P3) // looking right
	{
		game->render->ray_x = (((int)game->render->player_x / TILE) * TILE) + TILE;
		// game->render->ray_y = (game->render->player_x - game->render->ray_x) * tan(game->render->ray_angle) + game->render->player_y;
		game->render->ray_y = game->render->player_y + (game->render->ray_x - game->render->player_x) * tan(game->render->ray_angle);
		game->render->x_offset = TILE; 
		game->render->y_offset = game->render->x_offset * tan(game->render->ray_angle); 
	}
	else if (game->render->ray_angle == P2 || game->render->ray_angle == P3) // looking straight up or down
	{
		game->render->ray_x = game->render->player_x;
		game->render->ray_y = game->render->player_y;
		game->render->dof = max_dof;
	}
}

void	check_vertical_lines(t_game *game, float n_tan)
{
	(void)n_tan;
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
		 if (game->render->m_x >= 0 && game->render->m_x < (int)game->map_info.max_len &&
            game->render->m_y >= 0 && game->render->m_y < (int)game->map_info.num_rows)
		{
			if (game->map[game->render->m_y][game->render->m_x] == '1')
			{
				game->render->vertical_ray_x_pos = game->render->ray_x;
				game->render->vertical_ray_y_pos = game->render->ray_y;
				game->render->v_distance = distance(game->render->player_x, game->render->player_y, game->render->vertical_ray_x_pos, game->render->vertical_ray_y_pos, game->render->ray_angle);
				if (game->render->ray_angle > P2 && game->render->ray_angle < P3) // Ray pointing left
					game->render->wall_dir = EAST;
				else
					game->render->wall_dir = WEST;
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

// function that will return the distance between the player and the rays end point


void	draw_rays(void  *param)
{
	float		a_tan;
	float		n_tan;
	float		ray_angle_increment;
	t_game	*game;

	game = (t_game *)param;
 	if (!game || !game->render->ray_image || !game->render->ray_image->pixels)
        return;
	ft_memset(game->render->ray_image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	//calculate the field of view in radians (60 degrees = PI/3)
	game->render->fov = PI / 3;
	ray_angle_increment = game->render->fov / WIDTH; // half width for right side 3d view
	game->render->ray_angle = game->render->player_angle - (game->render->fov / 2);
	// printf("ray_angle[%f]\n", game->render->ray_angle);
	//angle normalization
	normalize_angle(game);
	game->render->ray = 0;
	// printf("----------------------------------\n");
	// printf("[%f]\n", game->render->ray_angle);
	while (game->render->ray < WIDTH) // rays for right half only
	{	//distance from player to an intersection on the horizontal and vertical grids. 
		//set to a really high value so that the real wall intersection will be closer and replace these default values
		game->render->h_distance = 1000000; 
		game->render->v_distance = 1000000;
		//----------------------------------------------------------------------------------------
		game->render->dof = 0; //dof is distance of field and means the amount of grid cells we search for a wall before giving
		normalize_angle(game);
		// printf("[%f]\n", game->render->ray_angle);
		//------------------------------------
		n_tan = -tan(game->render->ray_angle); //vertical line intersection calculations
		a_tan = -1 / tan(game->render->ray_angle); //horizontal line intersection calculations
		game->render->dof = 0;
		check_horizontal_lines(game, a_tan);
		game->render->wall_dir_h = game->render->wall_dir;
		game->render->dof = 0; 
		check_vertical_lines(game, n_tan);
		game->render->wall_dir_v = game->render->wall_dir;

		//if statements implent the closest intersection selection logic
		//	if the vertical wall intersec is closer that horizontal one we set the ray endpoint to the vert intersec coordinates
		//	and use the vertical ray intersection as the final distance. this means the ray hit a vertical wall (n or s) 
		if (game->render->v_distance < game->render->h_distance)
		{
			game->render->ray_x = game->render->vertical_ray_x_pos;
			game->render->ray_y = game->render->vertical_ray_y_pos;
			game->render->final_dist = game->render->v_distance;
			game->render->wall_hit_x = game->render->vertical_ray_x_pos;
			game->render->wall_hit_y = game->render->vertical_ray_y_pos;
			//game->render->wall_dir = game->render->wall_dir_v;
		}
		//	if the horizontal wall intersec is closer that vertical one we set the ray endpoint to the horizontal intersec coordinates
		//	and use the horizontal ray intersection as the final distance. this means the ray hit a horizontal wall (e or w) 
		if (game->render->h_distance < game->render->v_distance)
		{
			game->render->ray_x = game->render->horizontal_ray_x_pos;
			game->render->ray_y = game->render->horizontal_ray_y_pos;
			game->render->final_dist = game->render->h_distance;
			game->render->wall_hit_x = game->render->horizontal_ray_x_pos;
			game->render->wall_hit_y = game->render->horizontal_ray_y_pos;
			//game->render->wall_dir = game->render->wall_dir_h;

		}

		game->render->correct_distance = game->render->final_dist * cos(game->render->ray_angle - game->render->player_angle); //fisheye correction
		
		if (game->render->correct_distance < 1.0) //prevent division by zero 
			game->render->correct_distance = 1.0;
		
		game->render->line_height = (64 * HEIGHT) / game->render->correct_distance; //calculate wall height based on the distance
		
		// cap the line height. maintainst visual consistency regardless of player distance to the wall. and prevents renderer from drawing wall too high
		if (game->render->line_height > HEIGHT)
			game->render->line_height = HEIGHT;
		if (game->render->line_height < 1)
			game->render->line_height = 1;
		// only draw every 8th ray to avoid cluttering the 2d view
		if (game->render->ray % 32 == 0)
			draw_line(game->render, (int)game->render->player_x, (int)game->render->player_y, (int)game->render->ray_x, (int)game->render->ray_y);
		//line offset
		game->render->line_offset = (HEIGHT / 2) - (game->render->line_height / 2);
		draw_col(game);
		
		
		game->render->ray++;
		game->render->ray_angle += ray_angle_increment;
		
	}
	// printf("player angle: %f\n", game->render->player_angle);
}

float	get_xcoord_from_texture(t_game *game)
{
	float 	wall_offset;
	float 	tex_coord;
	int		maxw;

	if (game->render->wall_dir == NORTH)
	{
		wall_offset = fmodf(game->render->wall_hit_x, TILE);
		tex_coord = wall_offset * game->textures->north_t->width / TILE;
		
	}
	else if (game->render->wall_dir == SOUTH)
	{
		wall_offset = TILE - fmodf(game->render->wall_hit_x, TILE);
		tex_coord = wall_offset * game->textures->south_t->width / TILE;
	}
	else if (game->render->wall_dir == EAST)
	{
		wall_offset = fmodf(game->render->wall_hit_y, TILE);
		tex_coord = wall_offset * game->textures->east_t->width / TILE;
	}
	else if (game->render->wall_dir == WEST)
	{
		wall_offset = TILE - fmodf(game->render->wall_hit_y, TILE);
		tex_coord = wall_offset * game->textures->west_t->width / TILE;
	}
	else
		return 0.0f; // Fallback
	// Clamp
	if (tex_coord < 0)
		tex_coord = 0;
	// Clamp to width-1 for safety for all directions:
	maxw = 0;
	if      (game->render->wall_dir == SOUTH) maxw = game->textures->south_t->width;
	else if (game->render->wall_dir == NORTH) maxw = game->textures->north_t->width;
	else if (game->render->wall_dir == EAST)  maxw = game->textures->east_t->width;
	else if (game->render->wall_dir == WEST)  maxw = game->textures->west_t->width;
	if (tex_coord >= maxw) tex_coord = maxw - 1;
	
	return tex_coord;
}


