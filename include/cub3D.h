#ifndef CUB3D_H
# define CUB3D_H

// INCLUDES
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h> //TODO check that it is used, remove if not
# include <string.h>
# include <math.h>
# include <limits.h>
# include "libft.h"

// MACROS
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307
# define KEY_M 109
# define KEY_Q 113

# define WINDOW_WIDTH 950
# define WINDOW_HEIGHT 950
# define TILE_SIZE 64
# define SCALE_FACTOR 0.5
# define MINI_TILE (TILE_SIZE * SCALE_FACTOR)
# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV (60 * (3.14159265 / 180))
# define NUM_RAYS WINDOW_WIDTH

# define FALSE 0
# define TRUE 1

// BASIC COLORS
# define RED 0xFF0000
# define LGREY 0x808080
# define GREY 0x505050
# define BLACK 0x1000000
# define WHITE 0xFFFFFF
# define LIME 0x00FF00 
# define GREEN 0x008000 
# define PURPLE 0x800080 
# define TEAL 0x008080 
# define BLUE 0x0000FF 
# define AQUA 0x00FFFF

# define SOL_1 0xF89F5B
# define XMUR_1 0xE53F71
# define YMUR_1 0x9C3587
# define PLA_1 0x653780

# define SOL_2 0x3F1651
# define XMUR_2 0x3F1651
# define YMUR_2 0x3F1651
# define PLA_2 0x3F1651

// STRUCTURES
typedef struct	s_player
{
	int					move;
	int					rot;
	double				rot_angle;
	double				x;
	double				y;
}						t_player;

typedef struct s_ray {
	float				ray_angle;
	float				wall_hit_x;
	float				wall_hit_y;
	float				distance;
	int					was_hit_vertical;
	int					is_ray_facing_up;
	int					is_ray_facing_down;
	int					is_ray_facing_left;
	int					is_ray_facing_right;
}						t_ray;

typedef struct s_coord
{
	int					x0;
	int					y0;
	int					x1; // also used for height
	int					y1; // also used for width
}						t_coord;

typedef struct s_map
{
	char				**file_contents;
	char				**map;
	char				*map_name;
	int					sprite_size;
	int					map_fd;
	int					map_height;
	int					map_width;
	int					file_line_count;
	//int				player_position[2];
	int					win_width;
	int					win_height;
	int					is_minimap_open;
	char				**spltd;
	struct s_params		*params;
	struct s_mlx		*graphics;
	struct s_coord		coord;
	struct s_player		plyr;
	struct s_ray		rays[NUM_RAYS];
}						t_map;

typedef struct	s_img
{
	void				*image;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	int					sprite_size;
}						t_img;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*window_ptr;
	void				*minimap_window_ptr;
	t_img				game_img;
	t_img				minimap_img;
	int					minimap_height;
	int					minimap_width;
	int					minimap_tile;
	double				minimap_dot_pos[2];
	int					minimap_draw_end[2];
}						t_mlx;

typedef struct s_params
{
	t_img				n_texture;
	t_img				s_texture;
	t_img				e_texture;
	t_img				w_texture;
	int					f_rgb_color[3];
	int					c_rgb_color[3];
	int					c_color;
	int					f_color;
	int					pl_start_pos[2];
}						t_params;

typedef struct s_projection {
	float				perp_distance;
	float				distance_proj_plane;
	float				projected_wall_height;
	int					wall_strip_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
}						t_projection;

typedef struct s_raycasting {
	float				ray_angle;
	int					ray_is_facing_down;
	int					ray_is_facing_up;
	int					ray_is_facing_right;
	int					ray_is_facing_left;
	float				x_to_check;
	float				y_to_check;
	float				x_intercept;
	float				y_intercept;
	float				x_step;
	float				y_step;
	float				horz_hit_distance;
	float				vert_hit_distance;
	float				next_horz_touch_x;
	float				next_horz_touch_y;
	int					found_horz_wall_hit;
	float				horz_wall_hit_x;
	float				horz_wall_hit_y;
	float				next_vert_touch_x;
	float				next_vert_touch_y;
	int					found_vert_wall_hit;
	float				vert_wall_hit_x;
	float				vert_wall_hit_y;
}						t_raycasting;

// map_check_borders.c
void		closed_map_check();

// map_check_colors.c
void		check_color_values(char **line);
void		init_map_colors(char **line);
int			check_for_colors(char *line);
void		multi_freetab(char ***tab1, char ***tab2);

// map_check_file.c
void		map_name_checker(void);
int			map_file_checker(void);

// map_check_textures.c
void		check_for_texture(char *line);
void		assign_texture_parameters(t_img *texture,
				void *sprite, int sprite_size);
void		analyse_texture(char **args, void *sprite, int sprite_size);
void		check_and_store_path(char **args);
void		check_for_double_textures(char **args);

// map_parsing.c
void		map_parsing(void);
void		extract_map_file(void);
int			all_map_params_are_set(void);
int			correct_parameter_type(char *line);
void		process_map_file_contents(void);

// map_parsing_utils.c
int			is_map_character(char c);
int			line_contains_parameter(char *line);
void		set_player_start_angle(char player_char);
void		check_map_line(char *line, int i);
int			is_start_position(char c);

// map_parsing_utils2.c
void		get_file_dimensions(void);
void		get_map_dimensions(void);
void		map_last_in_file_check(void);
int			is_path_directory(char *path);
void		assign_color(int *color_ptr, int rgb[3]);

// map_structure.c
t_map		*_map(void);
void		map_struct_init(t_map *map);
void		params_struct_init(t_map *map);
void		graphics_struct_init(t_map *map);

// mlx_move_setup.c
void		trigger_minimap(void);
int			key_press(int key, void *param);
int			key_release(int key, void *param);
void		move_player(void);

// mlx_render_utils.c
void		ft_pixel_put(t_img *img, int x, int y, int color);
void		ft_put_rectangle(t_img *img, int color);
void		ft_put_rectangle_gradient(t_img *img, int color);
void		ft_put_circle(t_img *img, double pos[2], int radius, int color);
void		ft_draw_line(t_img *img, int color);

// mlx_setup.c
void		mlx_setup(void);
int			update_window(void);
void		init_hooks(void);

// raycasting.c
void		calculate_wall_hit_distances(t_raycasting *r);
void		find_horz_grid_intersection(t_raycasting *r);
void		find_vert_grid_intersection(t_raycasting *r);
void		cast_ray(float ray_angle, int strip_id);
void		cast_all_rays(void);

// raycasting_init.c
void		init_horz_intercepts(t_raycasting *r);
void		init_vert_intercepts(t_raycasting *r);
void		init_raycasting_values(t_raycasting *r, float ray_angle);

// raycasting_utils.c
float		normalize_angle(float angle);
float		distance_between_points(float x1, float y1, float x2, float y2);
int			map_has_wall_at(float x, float y);
void		coords_init(int x0, int y0, int x1, int y1);

// render_srawing.c
t_img		*pick_texture(int i);
void		draw_sky(t_projection p, int i);
void		draw_walls(t_projection p, int i);
void		draw_floor(t_projection p, int i);

// render_minimap.c
void		render_minimap(t_mlx *g, char **map);
void		render_player_dot_on_minimap();
void		init_minimap_values(int draw_pos[2], int draw_end[2]);
void		render_rays(void);

// render_wall_projection.c
void		generate_projection(void);
void		init_projection_values(t_projection *p, int i);

// utils.v
int			error_print(char *error, int return_value);
int			exit_game(void);
void		ft_exit(char *error, int exit_code);
void		free_all(void);
int			color_generator(u_int8_t red, u_int8_t green, u_int8_t blue);

#endif
