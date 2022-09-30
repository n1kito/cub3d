
#ifndef CUB3D_H
# define CUB3D_H

// INCLUDES

# include <mlx.h>
# include "mlx.h" // TODO check
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h> //TODO check that it is used, remove if not
# include <string.h>
# include "libft.h"

// MACROS

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define WALL 1

// STRUCTURES

typedef struct s_map
{
	char				**file_contents; // TODO rename this variable to file_contents
	char				**map;
	char				*map_name;
	int					sprite_size;
	int					map_fd;
	int					map_line_count;
	int					file_line_count;
	int					column_count;
	int					player_position[1];
	int					start_pos_count;
	int					win_width;
	int					win_height;
	struct s_params		*params;
	struct s_mlx		*graphics;
}				t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
}				t_mlx;

typedef struct s_params
{
	void	*n_texture;
	void	*s_texture;
	void	*e_texture;
	void	*w_texture;
	int		f_color[3];
	int		c_color[3];
}				t_params;

// error.c
int			error_print(char *error, int return_value);

// free.c
void		free_all();

// map_checker.c
void		check_color_values(char *line);
int			check_for_colors(char *line);
void		map_name_checker();
int			map_file_checker();

// map_texture_checking.c
void		check_for_texture(char *line);
void		check_and_store_path(char **args);
void		check_for_double_textures(char **args);
int			is_path_directory(char *path);

// map_parsing.c
void		map_parsing();
void		extract_map_file();
int			all_map_params_are_set();
int			correct_parameter_type(char *line);
void		process_map_file_contents();

// map_parsing_utils.c
void		get_map_dimensions();
int			is_map_character(char c);
int			line_is_part_of_map(char *line);

// map_structure.c
t_map		*_map();
void		map_struct_init(t_map *map);

#endif
