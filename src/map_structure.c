#include "cub3D.h"

t_map	*_map()
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			exit(error_print("could not malloc map", 1));
		map_struct_init(map); // TODO create
	}
	return (map);
}

void	map_struct_init(t_map *map)
{
	map->map_name = NULL;
	map->map = NULL;
	map->params = NULL;
	map->graphics = NULL;
}
