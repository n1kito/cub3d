#include "cub3D.h"

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

void	map_struct_init(t_map *map)
{
	map->map_name = NULL;
	map->file_contents = NULL;
	map->map = NULL;
	map->params = NULL;
	map->params = malloc(sizeof(t_params));
	if (!map->params)
		ft_exit("malloc fail [map_struct_init()][1]", 1);
	map->params->n_texture = NULL;
	map->params->s_texture = NULL;
	map->params->e_texture = NULL;
	map->params->w_texture = NULL;
	map->params->c_color[0] = -1;
	map->params->f_color[0] = -1;
	map->graphics = NULL;
	map->graphics = malloc(sizeof(t_mlx));
	if (!map->graphics)
		ft_exit("malloc fail [map_struct_init()][2]", 1);
	map->graphics->mlx_ptr = NULL;
	map->graphics->window_ptr = NULL;
	map->tmp_split_line = NULL;
}
