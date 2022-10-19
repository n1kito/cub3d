//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

int	error_print(char *error, int return_value)
{
	static int	is_first_error = 0;

	if (is_first_error++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (return_value);
}

int	exit_game(void)
{
	ft_exit(NULL, 0);
	exit(0);
}

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
	// in params the paths need to be freed
	ft_freetab(&_map()->file_contents);
	free(_map());
}

/* Returns an int containing the RGB color values passed as parameter. */
int	color_generator(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
