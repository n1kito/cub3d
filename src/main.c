#include "cub3D.h"

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 2)
		return (error_print("map needed to launch ./cub3D", 1));
	(void)argv;
	(void)argc;
	(void)env;
	_map();
	_map()->map_name = argv[1];
	mlx_setup();
	map_file_checker();
	map_parsing();
	init_hooks();
	mlx_loop(_map()->graphics->mlx_ptr);
	// game process
	// 	- process player input
	// 	- update image
	//	- render image
	return (free_all(), 0);
}
