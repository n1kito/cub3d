#include "cub3D.h"

int	error_print(char *error, int return_value)
{
	static int	is_first_error = 0;

	if (is_first_error++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (return_value);
}