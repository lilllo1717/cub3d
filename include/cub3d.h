#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX/include/MLX42/MLX42.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define DR 0.0174533 //one degree in radians, used to seperate each ray by 1 degree
# define WIDTH 1920
# define HEIGHT 1080
# define PLAYER_COLOR 0x00FFFFFF
# define WALL 0xFF0000FF
# define FLOOR 0x00FFFF30
# define EMPTY 0x00000000
# define PI 3.1415926535
# define P2 (PI / 2)
# define P3 (3 * PI / 2)
# define TILE 64
# define MINITILE 16
# define SOUTH 0
# define NORTH 1
# define EAST 2
# define WEST 3
# define M_SPEED 150.0
# define PLAYER_SIZE 10

enum					keys_texture
{
	KEY_NO,
	KEY_SO,
	KEY_WE,
	KEY_EA,
	NUM_KEYS1
};

enum					player_chars
{
	KEY_N,
	KEY_S,
	KEY_W,
	KEY_E,
};

enum					keys_colors
{
	KEY_F,
	KEY_C,
	NUM_KEYS2
};

typedef struct s_draw
{
	mlx_texture_t		*wall_t;
    int					tex_x;
	int					tex_y;
    float				tex_step;
	float				tex_y_offset;
    int					y;
	uint32_t			pixel_color; 
    int					wall_start;
    int					wall_end;
} 						t_draw;


typedef struct s_render
{
	mlx_t				*mlx;
	mlx_image_t			*player_image;
	mlx_image_t			*ray_image;
	float				player_x;
	float				player_y;
	float				player_delta_x;
	float				player_delta_y;
	float				player_angle;
	float				ray_angle;
	float				ray_y;
	float				ray_x;
	float				h_distance;
	float				v_distance;
	float				horizontal_ray_x_pos; //horizontal ray's x positions
	float				horizontal_ray_y_pos; //horizontal ray's y positions
	float				vertical_ray_x_pos; //vertical ray's x positions
	float				vertical_ray_y_pos; //vertical ray's y positions
	float				line_height;
	float				line_offset;
	float				correct_distance;
	float				fov;
	int					ray;
	float				y_offset;
	float				x_offset;
	int 				dof;
	float				final_dist;
	int					m_x;
	int					m_y;
	int					mp;
	int					wall_dir; //direction of the wall that was hit by a ray. 0=N,1=S,2=E,3=W
	float				wall_hit_x;
	float				wall_hit_y;
	int					wall_dir_h;
	int					wall_dir_v;
}						t_render;

typedef struct s_texture
{
	char				*n_text;
	char				*s_text;
	char				*w_text;
	char				*e_text;
	mlx_texture_t		*north_t;
	mlx_texture_t		*south_t;
	mlx_texture_t		*east_t;
	mlx_texture_t		*west_t;
}						t_texture;

typedef struct s_color
{
	char				*f_color;
	char				*c_color;
	unsigned long		f_rgb;
	unsigned long		c_rgb;
}						t_color;

typedef struct s_map
{
	size_t				max_len;
	size_t				num_rows;
	char				player_letter;
	int					player_flag;
}						t_map;

typedef struct s_game
{
	char				**initial_file;
	char				**map;
	struct s_texture	*textures;
	struct s_color		*colors;
	struct s_render		*render;
	struct s_map		map_info;
	struct s_draw		*draw;
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
int						validate_map(t_game *game, char **initial_file,
							t_render *render);
char					**map_for_valid(char **file, t_map *map_dim);
int						ft_dfs_inside(char **map, size_t row, size_t col,
							t_map *map_dim);
bool	map_chars_valid(t_game *game, char **map, t_map *map_for_pos);
void					find_player_position(char **map, t_render *render,
							t_map *map_for_pos);
int						init_game_parsing(t_game *game);
int						implement_parsing(t_game *game, t_render *render, 
							int argc, char **argv);
/*utils*/
void					free_2darray_partial(char **arr, int num);
void					free_2darray(char **arr);
void					print_2d_array(char **arr);
int						ft_count_substrings(const char *s, char c);
void					free_2dint_partial(int **arr, int num);
void					free_2dint(int **arr);
int						parse_colors(t_game *game);
void					copy_string(char *checking_char, char *color);
int						parse_textures(t_game *game);
int						malloc_map(char **map, t_map *map_dim);
void					free_game(t_game *game);
int						init_game_parsing(t_game *game);
void					err(char *str);
void					free_render(t_render *render);
void					free_step2(t_game *game);
void					free_invalid_map(t_game *game);

/* ----mlx---- */
t_render				*init_render(void);
int						mlx_start(t_game *game);
void					draw_player(void *param);
void					key_handler(mlx_key_data_t keydata, void *param);
void					create_world(void *param);
void					put_tile(mlx_image_t *image, int start_x, int start_y,
							uint32_t color);
void					draw_rays(void *param);
int						draw_line(t_render *render, int begin_x, int begin_y, int end_x, int end_y);
void					draw_col(t_game *game);
void					check_horizontal_lines(t_game *game, float a_tan);
void					check_vertical_lines(t_game *game, float n_tan);
void					render_frame(void *param);
/* ---movement------ */
void					left_right(t_game *game);
void					forward_backward(t_game *game);
void					turn(t_game *game);
void    				mouse_handler(double xpos, double ypos, void* param);

/* ----render utils---- */
float					distance(float ax, float ay, float bx, float by);
void					normalize_angle(t_game *game);
int						determine_steps(float delta_x, float delta_y);
/* -- textures --*/
void					put_textures(t_game *game, int wall_start, int wall_end, int col_x, int y);
int						load_textures(t_game *game);
float					get_xcoord_from_texture(t_game *game);
mlx_texture_t 			*select_correct_texture(t_game *game);


/*----rays------*/
void					setup_horizontal_rays(t_game *game, int max_dof);
void					horizontal_wall_detection(t_game *game, int max_dof);
void					setup_vertical_rays(t_game *game, int max_dof);
void					vertical_wall_detection(t_game *game, int max_dof);



#endif