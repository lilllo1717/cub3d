#include "cub3d.h"

void	draw_rays(t_render *render)
{
	float	a_tan;

	ft_memset(render->ray_image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	render->ray_angle = render->player_angle;
	render->ray = 0;
	while (render->ray < 1)
	{
		render->dof = 0;
		//check horizontal lines
		a_tan = -1 / tan(render->ray_angle);
		if (render->ray_angle > PI) // looking up
		{
			render->ray_y = (((int)render->player_y / 64) * 64) - 0.0001;
			render->ray_x = (render->player_y - render->ray_y) * a_tan + render->player_x;
			render->y_offset = -64; 
			render->x_offset = render->y_offset * a_tan; 
		}
		if (render->ray_angle < PI) // looking down
		{
			render->ray_y = (((int)render->player_y / 64) * 64) + 64;
			render->ray_x = (render->player_y - render->ray_y) * a_tan + render->player_x;
			render->y_offset = 64; 
			render->x_offset = render->y_offset * a_tan; 
		}
		if (render->ray_angle == 0 || render->ray_angle == PI) // looking straight left or right
		{
			render->ray_x = render->player_x;
			render->ray_y = render->player_y;
			render->dof = 8;
		}
		while (render->dof < 8)
		{
			render->m_x = (int)(render->ray_x) / 64;
			render->m_y = (int)(render->ray_y) / 64;
			render->mp = render->m_y * 25 + render->m_x;
			if (render->mp < 25 * 14 && render->map[render->mp] == 1)
				render->dof = 8;
			else
			{
				render->ray_x += render->x_offset;
				render->ray_y += render->y_offset;
			}
		}
		draw_line(render, (int)render->player_x, (int)render->player_y, (int)render->ray_x, (int)render->ray_y);
		
		render->ray++;
	}
	
}

static int	determine_steps(float delta_x, float delta_y)
{
	if (fabs(delta_x) > fabs(delta_y))
		return ((int)fabs(delta_x));
	else
		return ((int)fabs(delta_y));
}

int	draw_line(t_render *render, int begin_x, int begin_y, int end_x, int end_y)
{
	float	delta_x;
	float	delta_y;
	float	current_x;
	float	current_y;
	float	step_x;
	float	step_y;
	int		steps;
	int		i;

	i = 0;
	delta_y = end_y - begin_y;
	delta_x = end_x - begin_x;
	steps = determine_steps(delta_x, delta_y);
	step_x = delta_x / steps;
	step_y = delta_y / steps;
	current_x = begin_x;
	current_y = begin_y;
	while (i <= steps)
	{
        if ((int)current_x >= 0 && (int)current_x < WIDTH && 
            (int)current_y >= 0 && (int)current_y < HEIGHT)
            mlx_put_pixel(render->ray_image, (int)current_x, (int)current_y, 0xFF0000FF);
        current_x += step_x;
        current_y += step_y;
		i++;
	}
	return (0);
}
