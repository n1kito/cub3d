#include "cub3D.h"

/* Called everytime a pointer to the main map structure is needed.
 * Initializes said map structure only on first call. */
t_map	*_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			ft_exit("could not malloc map", 1);
		map_struct_init(map);
	}
	return (map);
}


/* Allocated memoery for all elements of map structure
 * and initializes all pointers. */
void	map_struct_init(t_map *map)
{
	map->map_name = NULL;
	map->file_contents = NULL;
	map->map = NULL;
	map->params = NULL;
    map->graphics = NULL;
	map->plyr.rot_angle = 0;
	params_struct_init(map);
    graphics_struct_init(map);
}

void    params_struct_init(t_map *map)
{
    map->params = malloc(sizeof(t_params));
	if (!map->params)
		ft_exit("malloc fail [map_struct_init()][1]", 1);
	map->params->n_texture = NULL;
	map->params->s_texture = NULL;
	map->params->e_texture = NULL;
	map->params->w_texture = NULL;
	map->params->c_color[0] = -1;
	map->params->f_color[0] = -1;
	map->params->pl_start_pos[0] = -1;
	map->params->pl_start_pos[1] = -1;
}

void    graphics_struct_init(t_map *map)
{
	map->graphics = malloc(sizeof(t_mlx));
	if (!map->graphics)
		ft_exit("malloc fail [map_struct_init()][2]", 1);
	map->graphics->mlx_ptr = NULL;
	map->graphics->window_ptr = NULL;
	map->graphics->window_width = 1920;
	map->graphics->window_height = 1080;
	// map->graphics->minimap_tile = 64;
	map->graphics->minimap_tile = TILE_SIZE * SCALE_FACTOR;
	map->graphics->minimap_width = 11 * map->graphics->minimap_tile;
	map->graphics->minimap_height = map->graphics->minimap_width;
	// map->graphics->minimap_tile = map->graphics->minimap_width / 11;
}