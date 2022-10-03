#include "cub3D.h"

int	main(int argc, char *argv[], char *env[])
{
	// if (argc != 2)
		// return (error_print("wrong argument count", 1));
	(void)argv;
	(void)argc;
	(void)env;
	_map();
	_map()->map_name = "mapfile.cub";
	map_file_checker();
	map_parsing();
	closed_map_check();
	// game process
	// 	- process player input
	// 	- update image
	//	- render image
	return (0);
}
