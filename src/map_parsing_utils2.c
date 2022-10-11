#include "cub3D.h"

/* Stores the number of lines in the map as well as the length of the longest line. */
void	get_map_dimensions(void)
{
	int	map_height;
	int	map_width;
	int	map_width_tmp;

	map_width = 0;
	map_width_tmp = 0;
	map_height = 0;
	while (_map()->map[map_height])
	{
		map_width_tmp = 0;
		while (_map()->map[map_height][map_width_tmp])
			map_width_tmp++;
		if (map_width_tmp > map_width)
			map_width = map_width_tmp;
		map_height++;
	}
	_map()->map_height = map_height;
	_map()->map_width = map_width - 1;
}

/* Checks that there is nothing after the map in the file. */
void	map_last_in_file_check(void)
{
	char	**map_last_line;
	int		i;

	map_last_line = _map()->map + _map()->map_height;
	i = 0;
	while (map_last_line[++i])
		if (map_last_line[i]
			&& (map_last_line[i][0] != '\n')) // TODO this means we accept new lines after the map but nothing else
			ft_exit("map is not at the end of the file", 1);
	exit(0);
}