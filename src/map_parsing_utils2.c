//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Measures the number of lines and columns in the map and saves them in the
 * map structure. */
void	get_file_dimensions(void)
{
	char	*line;

	_map()->file_line_count = 0;
	while (1)
	{
		line = get_next_line(_map()->map_fd);
		if (!line)
			break ;
		_map()->file_line_count++;
		free(line);
	}
	free(line);
	if (_map()->file_line_count == 0)
		ft_exit("map is empty", 1);
}

/* Stores the number of lines in the map as well as
 * the length of the longest line. */
void	get_map_dimensions(void)
{
	int	map_height;
	int	map_width;
	int	map_width_tmp;

	map_width = 0;
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
	char	**after_map_last_line;
	int		line_index;

	after_map_last_line = _map()->map + _map()->map_height;
	line_index = after_map_last_line - _map()->file_contents;
	while (line_index < _map()->file_line_count)
	{
		if (_map()->file_contents[line_index]
			&& _map()->file_contents[line_index][0] != '\n')
			ft_exit("map is not at the end of the file", 1);
		line_index++;
	}
}
