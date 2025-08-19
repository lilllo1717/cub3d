#include "cub3d.h"

t_render	*init_render()
{
	t_render *render;
	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	ft_memset(render, 0, sizeof(t_render));
	return (render);
}

void	mlx_start(t_render *render)
{

	render->mlx = mlx_init(1024, 1024, "BEST GAME EVER", true);
	if (!render->mlx)
	{
		perror("Failed to initialize MLX42");
		exit(EXIT_FAILURE);
	}
}

