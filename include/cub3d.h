#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX/include/MLX42/MLX42.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# define MOVEMENT 10.0f
# define WIDTH 1920
# define HEIGHT 1080
# define PLAYER_COLOR 0xFF0000FF
# define WALL 0xFFFFFFFF
# define FLOOR 0x00FFFFFF
# define PI 3.1415926535 

enum					keys_texture
{
	KEY_NO,
	KEY_SO,
	KEY_WE,
	KEY_EA,
	NUM_KEYS1
};
enum					keys_colors
{
	KEY_F,
	KEY_C,
	NUM_KEYS2
};

typedef struct s_render
{
	mlx_t				*mlx;
	mlx_image_t			*player_image;
	float				player_x; 
	float				player_y;
	float				player_delta_x;
	float				player_delta_y;
	float				player_angle;

}						t_render;

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

typedef struct s_map
{
	size_t				max_len;
	size_t				num_rows;
}						t_map;

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
bool					is_map_last(char **map);
int						find_textures(char **map);
bool					no_invalid_input(char *line, int in_map);
int						count_num_lines(char *file);
int						parse_file(char **file);
bool					is_valid_color(char *file);
bool					is_valid_color_line(char *line);
bool					is_color(char *line);
bool					is_texture(char *line);
bool					is_color(char *line);
t_map					find_map_size(char **file);
int						validate_map(char **initial_file);
char					**map_for_valid(char **file, t_map *map_dim);

/*utils*/
void					free_2darray_partial(char **arr, int num);
void					free_2darray(char **arr);
void					print_2d_array(char **arr);
int						ft_count_substrings(const char *s, char c);
void					free_2dint_partial(int **arr, int num);
void					free_2dint(int **arr);

/*mlx*/
t_render				*init_render(void);
void					mlx_start(t_render *render);
void					draw_player(void *param);
void					key_handler(mlx_key_data_t keydata, void *param);
void					create_world(void *param);
void					put_tile(mlx_image_t *image, int start_x, int start_y,
							int size, uint32_t color);

#endif