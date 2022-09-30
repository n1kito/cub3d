#include "cub3D.h"

t_map	*_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			exit(error_print("could not malloc map", 1));
		map_struct_init(map);
	}
	return (map);
}

void	map_struct_init(t_map *map)
{
	map->map_name = NULL;
	map->map = NULL;
	map->params = NULL;
	map->graphics = NULL;
	map->params = malloc(sizeof(t_params));
	if (!map->params)
		exit(error_print("malloc fail [map_struct_init()][1]", 1));
	map->params->n_texture = NULL;
	map->params->s_texture = NULL;
	map->params->e_texture = NULL;
	map->params->w_texture = NULL;
}
