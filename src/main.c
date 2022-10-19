//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (error_print("map needed to launch ./cub3D", 1));
	_map();
	_map()->map_name = argv[1];
	mlx_setup();
	map_file_checker();
	map_parsing();
	init_hooks();
	mlx_loop(_map()->graphics->mlx_ptr);
	return (free_all(), 0);
}
