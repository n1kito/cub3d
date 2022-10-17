#include "cub3D.h"

/*
	Checks if the map ends with .cub
*/
void	map_name_checker(void)
{
	int	i;

	i = 0;
	while (_map()->map_name[i])
	{
		if (i == 0 && _map()->map_name[i] == '.' && _map()->map_name[1] == '/')
			i += 2;
		else if (_map()->map_name[i] == '.')
		{
			if (ft_strncmp(_map()->map_name + i + 1,
					"cub", ft_strlen("cub")) == 0)
				if (_map()->map_name[i + ft_strlen("cub") + 1] == '\0')
					return ;
			i++;
		}
		else
			i++;
	}
	ft_exit("wrong map name", 1);
}

/* */

int	map_file_checker(void)
{
	int	dir_test;
	int	*map_fd_tmp;

	map_fd_tmp = &_map()->map_fd;
	map_name_checker();
	dir_test = open(_map()->map_name, O_DIRECTORY);
	if (dir_test != -1)
	{
		close(dir_test);
		ft_exit("map argument is a directory", 1);
	}
	*map_fd_tmp = open(_map()->map_name, O_RDONLY);
	if (*map_fd_tmp == -1)
		ft_exit("map file could not be opened", 1);
	return (0);
}
