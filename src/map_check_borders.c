//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

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
			ft_printf_fd(2, "%s", _map()->map[x]);
			while (++y < j)
				write(2, "-", 1);
			write(2, "^", 2);
			ft_printf_fd(2, "    Map not closed on [%d][%d] !\n", i, j);
		}
		else
			ft_printf_fd(2, "%s", _map()->map[x]);
		x++;
	}
}

void	check_around(int i, int j)
{
	if (!_map()->map[i + 1])
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i + 1][j]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i - 1][j]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i][j + 1]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i][j - 1]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
}

void	closed_map_check(void)
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
