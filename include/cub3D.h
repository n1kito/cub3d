
#ifndef CUB3D_H
# define CUB3D_H

// INCLUDES

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
	char				**full_map_file;
	char				**map;
	char				*map_name;
	int					sprite_size;
	int					map_fd;
	int					line_count;
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
	int		*f_color;
	int		*c_color;
}				t_params;

// error.c
int			error_print(char *error, int return_value);

// free.c
void		free_all();

// map_checker.c
int			map_checker();
void		map_name_checker();
void		map_struct_init();

// map_structure.c
t_map		*_map();
void		map_struct_init(t_map *map);

#endif
