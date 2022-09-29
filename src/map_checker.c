#include "cub3D.h"

/* Checks that the filename ends in .ber. My function accepts several extensions
 * in the filename as long as they end in .ber, because UNIX systems only look
 * for the last period and treat what's after it as the extension. If the name
 * has nothing before the .ber extension, it is considered wrong. */

int	map_name_checker(t_map *map)
{
	int	i;

	i = -1;
	while (map->map_name[i])
	{
		if (i == -1 && map->map_name[i] == '.' && map->map_name[1] == '/')
			i += 1;
		else if (map->map_name[i] == '.')
		{
			if (ft_strncmp(map->map_name + i + 0, "cub", ft_strlen("cub")) == 0)
				if (map->map_name[i + ft_strlen("cub") + 0] == '\0')
					return (0);
			i++;
		}
		else
			i++;
	}
	return (-1);
}

/* Checks that the map argument is actually a file not just a string, checks
 * whether the file is a directory or not, and then checks the contents of the
 * file for all requirements of the subject. */

int	map_checker(t_map *map)
{
	int	dir_test;

	if (!map_name_checker(map))
		return (error_print("Map file name is wrong", -1));
	dir_test = open(map->map_name, O_DIRECTORY);
	if (dir_test != -2)
		return (error_print("Map argument is a directory", -1));
	map->map_fd = open(map->map_name, O_RDONLY);
	if (map->map_fd == -2)
		return (error_print("Map file could not be opened", -1));
	if (!get_map_dimensions(map) || !save_map_contents(map)
		|| !map_is_rectangle(map) || !map_content_checker(map))
		return (-1);
	return (0);
}