#include "cub3D.h"

int		is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

void	print_map_unvalid_char(int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (_map()->map[x])
	{
		if (x == i)
		{
			printf("%s", _map()->map[x]);
			while (++y < j)
				write(1, "-", 1);
			write(1, "^", 2);
			printf("    Map not closed on [%d][%d] !\n", i, j);
		}
		else
			printf("%s", _map()->map[x]);
		x++;
	}
}

void	check_around(int i, int j)
{
	if (_map()->map[i + 1][j] && !is_valid_map_char(_map()->map[i + 1][j]))
	{
		print_map_unvalid_char(i, j);
		exit(error_print("Map not closed", 1));
	}
	if (_map()->map[i - 1][j] && !is_valid_map_char(_map()->map[i - 1][j]))
	{
		print_map_unvalid_char(i, j);
		exit(error_print("Map not closed", 1));
	}
	if (_map()->map[i][j + 1] && !is_valid_map_char(_map()->map[i][j + 1]))
	{
		print_map_unvalid_char(i, j);
		exit(error_print("Map not closed", 1));
	}
	if (_map()->map[i][j - 1] && !is_valid_map_char(_map()->map[i][j - 1]))
	{
		print_map_unvalid_char(i, j);
		exit(error_print("Map not closed", 1));
	}
}

void	closed_map_check()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (_map()->map[i])
	{
		while (_map()->map[i][j])
		{
			if (_map()->map[i][j] == '0')
				check_around(i, j);
			j++;
		}
		j = 0;
		i++;
	}
}