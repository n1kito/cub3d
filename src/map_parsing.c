#include "cub3D.h"

/* Saves the map to a char** in my structure, and calls get_next_line() one
 * last time to clear the buffer and avoid leaks. */

int	save_map_contents()
{
	int	i;

	_map()->map = malloc(sizeof(char *) * _map()->line_count);
	if (!_map()->map)
	{
		get_next_line(-1);
		return (puterr("Could not allocate memory for first map", 0));
	}
	close(_map()->map_fd);
	_map()->map_fd = open(_map()->map_name, O_RDONLY);
	i = 0;
	while (i < _map()->line_count)
		_map()->map[i++] = get_next_line(_map()->map_fd);
	get_next_line(-1);
	if (!cleanup_map(_map()))
		return (0);
	return (1);
}

/* Measures the number of lines and columns in the map and saves them in the
 * map structure. */

int	get_map_dimensions()
{
	char	*line;

	_map()->actual_line_count = 0;
	while (1)
	{
		line = get_next_line(_map()->map_fd);
		if (!line)
			break ;
		_map()->line_count++;
		if (line[0] != '\n')
			_map()->actual_line_count++;
		if (_map()->actual_line_count && line[0] == '\n')
			break ;
		free(line);
	}
	free(line);
	if (_map()->actual_line_count == 0)
		return (puterr("Map is empty", 0));
	return (1);
}

void	map_parsing()
{
	// Create and init params structure
	// 1. count map lines
	// 2. extract map with GNL
	// 3. for each line call process_line() and store/test each argument in the structure
	// 4. when we get to a line that is part of the map, check that all map parameter pointers have been allocated
			// If not, free & exit
			// Otherwise, store pointer to first map line and call map_checker().
}