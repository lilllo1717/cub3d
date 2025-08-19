#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX/include/MLX42/MLX42.h"
//# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_render
{
	mlx_t				*mlx;
	float				player_x;
	float				player_y;
	
} 						t_render;

typedef struct s_texture
{
	char				*n_text;
	char				*s_text;
	char				*w_text;
	char				*e_text;
}						t_texture;

typedef struct s_color
{
	char				*f_color;
	char				*c_color;
}						t_color;

typedef struct s_game
{
	char				**initial_file;
	char				**map;
	struct s_texture	*textures;
	struct s_color		*colors;
	struct s_render		*render;
}						t_game;

/*parsing*/

bool					is_valid_input(int argc, char **argv);
bool					is_valid_input_file(char *file_name);
int						parse_map(t_game *game, char *file);

/*utils*/
void					free_2darray_partial(char **arr, int num);
void					free_2darray(char **arr);

/*mlx*/
void					mlx_start(t_render *render);
t_render				*init_render();

#endif