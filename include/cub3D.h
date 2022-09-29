
#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h> //TODO check that it is used, remove if not
# include <string.h>
# include "libft.h"

/* #############################################################################
 *  MACROS */

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define WALL 1

typedef struct s_map
{
	char				**tmp_map;
	char				**map;
	char				*map_name;
	int					sprite_size;
	int					map_fd;
	int					column_count;
	int					player_position[1];
	int					start_pos_count;
	int					win_width;
	int					win_height;
	struct s_sprites	*sprites;
	struct s_mlx		*graphics;
}				t_map;

typedef struct s_sprites
{
	//void	*p;
}				t_sprites;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
}				t_mlx;

#endif
