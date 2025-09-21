#include "cub3d.h"

static void	initial_ray_calc(t_game *game)
{
	game->render->h_distance = 1000000;
	game->render->v_distance = 1000000;
	game->render->dof = 0;
	normalize_angle(game);
	game->render->dof = 0;
	check_horizontal_lines(game);
	game->render->wall_dir_h = game->render->wall_dir;
	game->render->dof = 0;
	check_vertical_lines(game);
	game->render->wall_dir_v = game->render->wall_dir;
}

static void	select_closest_intersec(t_game *game)
{
	if (game->render->v_distance < game->render->h_distance)
	{
		game->render->ray_x = game->render->vertical_ray_x_pos;
		game->render->ray_y = game->render->vertical_ray_y_pos;
		game->render->final_dist = game->render->v_distance;
		game->render->wall_hit_x = game->render->vertical_ray_x_pos;
		game->render->wall_hit_y = game->render->vertical_ray_y_pos;
		game->render->wall_dir = game->render->wall_dir_v;
	}
	if (game->render->h_distance < game->render->v_distance)
	{
		game->render->ray_x = game->render->horizontal_ray_x_pos;
		game->render->ray_y = game->render->horizontal_ray_y_pos;
		game->render->final_dist = game->render->h_distance;
		game->render->wall_hit_x = game->render->horizontal_ray_x_pos;
		game->render->wall_hit_y = game->render->horizontal_ray_y_pos;
		game->render->wall_dir = game->render->wall_dir_h;
	}
}

static void	render_ray_col(t_game *game, float ray_angle_increment)
{
	game->render->correct_distance = game->render->final_dist
		* cos(game->render->ray_angle - game->render->player_angle);
	if (game->render->correct_distance < 1.0)
		game->render->correct_distance = 1.0;
	game->render->line_height = (64 * HEIGHT) / game->render->correct_distance;
	if (game->render->line_height < 1)
		game->render->line_height = 1;
	game->render->line_offset = (HEIGHT / 2) - (game->render->line_height / 2);
	draw_col(game);
	game->render->ray++;
	game->render->ray_angle += ray_angle_increment;
}

// function that will return the distance between the player and the rays end point
void	draw_rays(void *param)
{
	float		ray_angle_increment;
	t_game		*game;

	game = (t_game *)param;
	if (!game || !game->render->ray_image || !game->render->ray_image->pixels)
		return ;
	ft_memset(game->render->ray_image->pixels, 0, WIDTH * HEIGHT
		* sizeof(int32_t));
	game->render->fov = PI / 3;
	ray_angle_increment = game->render->fov / WIDTH;
	game->render->ray_angle = game->render->player_angle
		- (game->render->fov / 2);
	normalize_angle(game);
	game->render->ray = 0;
	while (game->render->ray < WIDTH)
	{
		initial_ray_calc(game);
		select_closest_intersec(game);
		render_ray_col(game, ray_angle_increment);
	}
}

// void	draw_rays(void  *param)
// {
// 	float		a_tan;
// 	float		n_tan;
// 	float		ray_angle_increment;
// 	t_game		*game;

// 	game = (t_game *)param;
//  	if (!game || !game->render->ray_image || !game->render->ray_image->pixels)
//         return;
// 	ft_memset(game->render->ray_image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
// 	//calculate the field of view in radians (60 degrees = PI/3)
// 	game->render->fov = PI / 3;
// 	ray_angle_increment = game->render->fov / WIDTH;
// 	game->render->ray_angle = game->render->player_angle - (game->render->fov / 2);
// 	// printf("ray_angle[%f]\n", game->render->ray_angle);
// 	//angle normalization
// 	normalize_angle(game);
// 	game->render->ray = 0;
// 	// printf("----------------------------------\n");
// 	// printf("[%f]\n", game->render->ray_angle);
// 	while (game->render->ray < WIDTH) // rays for right half only
// 	{	//distance from player to an intersection on the horizontal and vertical grids. 
// 		//set to a really high value so that the real wall intersection will be closer and replace these default values
// 		game->render->h_distance = 1000000; 
// 		game->render->v_distance = 1000000;
// 		//----------------------------------------------------------------------------------------
// 		game->render->dof = 0; //dof is distance of field and means the amount of grid cells we search for a wall before giving
// 		normalize_angle(game);
// 		// printf("[%f]\n", game->render->ray_angle);
// 		//------------------------------------
// 		n_tan = -tan(game->render->ray_angle); //vertical line intersection calculations
// 		a_tan = -1 / tan(game->render->ray_angle); //horizontal line intersection calculations
// 		game->render->dof = 0;
// 		check_horizontal_lines(game, a_tan);
// 		game->render->wall_dir_h = game->render->wall_dir;
// 		game->render->dof = 0; 
// 		check_vertical_lines(game, n_tan);
// 		game->render->wall_dir_v = game->render->wall_dir;

// 		//if statements implement the closest intersection selection logic
// 		//	if the vertical wall intersec is closer that horizontal one we set the ray endpoint to the vert intersec coordinates
// 		//	and use the vertical ray intersection as the final distance. this means the ray hit a vertical wall (n or s) 
// 		if (game->render->v_distance < game->render->h_distance)
// 		{
// 			game->render->ray_x = game->render->vertical_ray_x_pos;
// 			game->render->ray_y = game->render->vertical_ray_y_pos;
// 			game->render->final_dist = game->render->v_distance;
// 			game->render->wall_hit_x = game->render->vertical_ray_x_pos;
// 			game->render->wall_hit_y = game->render->vertical_ray_y_pos;
// 			game->render->wall_dir = game->render->wall_dir_v;
// 		}
// 		//	if the horizontal wall intersec is closer that vertical one we set the ray endpoint to the horizontal intersec coordinates
// 		//	and use the horizontal ray intersection as the final distance. this means the ray hit a horizontal wall (e or w) 
// 		if (game->render->h_distance < game->render->v_distance)
// 		{
// 			game->render->ray_x = game->render->horizontal_ray_x_pos;
// 			game->render->ray_y = game->render->horizontal_ray_y_pos;
// 			game->render->final_dist = game->render->h_distance;
// 			game->render->wall_hit_x = game->render->horizontal_ray_x_pos;
// 			game->render->wall_hit_y = game->render->horizontal_ray_y_pos;
// 			game->render->wall_dir = game->render->wall_dir_h;

// 		}

// 		game->render->correct_distance = game->render->final_dist * cos(game->render->ray_angle - game->render->player_angle); //fisheye correction
		
// 		if (game->render->correct_distance < 1.0) //prevent division by zero 
// 			game->render->correct_distance = 1.0;
		
// 		game->render->line_height = (64 * HEIGHT) / game->render->correct_distance; //calculate wall height based on the distance

// 		// cap the line height. maintainst visual consistency regardless of player distance to the wall. and prevents renderer from drawing wall too high
// 		// if (game->render->line_height > HEIGHT)
// 		// 	game->render->line_height = HEIGHT;
// 		if (game->render->line_height < 1)
// 			game->render->line_height = 1;
// 		// only draw every 8th ray to avoid cluttering the 2d view
// 		// if (game->render->ray % 32 == 0)
// 		// 	draw_line(game->render, (int)game->render->player_x, (int)game->render->player_y, (int)game->render->ray_x, (int)game->render->ray_y);
// 		//line offset
// 		game->render->line_offset = (HEIGHT / 2) - (game->render->line_height / 2);
// 		draw_col(game);
// 		game->render->ray++;
// 		game->render->ray_angle += ray_angle_increment;

// 	}
// }