
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
# include "libft.h"

// MACROS

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define WALL 1

// BASIC COLORS

# define RED 0xFF0000
# define GREY 0x808080
# define BLACK 0x1000000
# define WHITE 0xFFFFFF

// STRUCTURES

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
	int					player_position[2];
	int					win_width;
	int					win_height;
	char				**spltd;
	struct s_params		*params;
	struct s_mlx		*graphics;
	struct s_coord		*coord;
}				t_map;

typedef struct s_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_coord
{
	int		x0;
	int		y0;
	int		x1; // also used for height
	int		y1; // also used for width
}				t_coord;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_img	game_img;
	t_img	minimap_img;
	int		window_height;
	int		window_width;
	int		minimap_height;
	int		minimap_width;
	int		minimap_tile;
}				t_mlx;

typedef struct s_params
{
	void	*n_texture;
	void	*s_texture;
	void	*e_texture;
	void	*w_texture;
	int		f_color[3];
	int		c_color[3];
	int		pl_start_pos[2];
}				t_params;

// error.c
int			error_print(char *error, int return_value);

// exit.c
void		ft_exit(char *error, int exit_code);
void		free_all(void);

// map_checker.c
void		map_name_checker(void);
int			map_file_checker(void);

// closed_map_checker.c
void		closed_map_check();

// map_color_checking.c
void		check_color_values(char **line);
void		init_map_colors(char **line);
int			check_for_colors(char *line);

// map_texture_checking.c
void		check_for_texture(char *line);
void		check_and_store_path(char **args);
void		check_for_double_textures(char **args);
int			is_path_directory(char *path);

// map_parsing.c
void		map_parsing(void);
void		extract_map_file(void);
int			all_map_params_are_set(void);
int			correct_parameter_type(char *line);
void		process_map_file_contents(void);

// map_parsing_utils.c
void		get_file_dimensions(void);
int			is_map_character(char c);
// int			line_is_part_of_map(char *line);
int			line_contains_parameter(char *line);
void		check_map_line(char *line, int i);
int			is_start_position(char c);

// map_structure.c
t_map		*_map(void);
void		map_struct_init(t_map *map);
void        params_struct_init(t_map *map);
void        graphics_struct_init(t_map *map);

// mlx_render_utils.c
int			color_generator(u_int8_t red, u_int8_t green, u_int8_t blue);
void		ft_pixel_put(t_img *img, int x, int y, int color);
void		ft_put_rectangle(t_img *img, int color);
void		ft_put_circle(t_img *img, int x, int y, int radius, int color);
void        ft_draw_line(t_img *img, int color);

// mlx_setup.c
void		mlx_setup(void);
void		init_hooks(void);

// render_minimap.c
void    	render_minimap(t_mlx *g, char **map);
void   		render_player_dot_on_minimap(int *draw_end);
void    	init_minimap_values(int *draw_pos, int *draw_end);

// map_coord_init.c
void 	   coords_init(int x0, int y0, int x1, int y1);
void		free_coords();

#endif
