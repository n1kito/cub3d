#include "cub3D.h"

void	ft_exit(char *error, int exit_code)
{
	if (error)
		error_print(error, 0);
	free_all();
	exit(exit_code);
}

void	free_all(void)
{
	// TODO add destroy functions
	free(_map()->graphics);
	free(_map()->params);
	ft_freetab(&_map()->file_contents);
	free(_map());
}
