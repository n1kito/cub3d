#include "cub3D.h"

int	error_print(char *error, int return_value)
{
	static int	is_first_error = 0;

	if (is_first_error++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (return_value);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 2)
		return (error_print("wrong argument count", 1));
	(void)argv;
	(void)env;
	// map_file_checker()
	// map_parsing()
	// game process
	// 	- process player input
	// 	- update image
	//	- render image
	return (0);
}
