#include "cub3D.h"

void	map_parsing()
{
	// Create and init params structure
	// 1. count map lines
	get_map_dimensions();
	// 2. extract map with GNL
	extract_map_file();
	// 3. process map file contents
	process_map_file_contents();
	// 3. for each line call process_line() and store/test each argument in the structure
	// 4. when we get to a line that is part of the map, check that all map parameter pointers have been allocated
			// If not, free & exit
			// Otherwise, store pointer to first map line and call map_checker().
	// check_map_contents();
}


/* Measures the number of lines and columns in the map and saves them in the
 * map structure. */

void	get_map_dimensions()
{
	char	*line;

	_map()->file_line_count = 0;
	while (1)
	{
		line = get_next_line(_map()->map_fd);
		if (!line)
			exit(error_print("gnl fail", 1)) ;
		_map()->line_count++;
		if (line[0] != '\n')
			_map()->file_line_count++;
		if (_map()->file_line_count && line[0] == '\n')
			break ;
		free(line);
	}
	free(line);
	if (_map()->file_line_count == 0)
		exit(error_print("map is empty", 1));
}


/* Saves the map to a char** in my structure, and calls get_next_line() one
 * last time to clear the buffer and avoid leaks. */

void	extract_map_file()
{
	int	i;

	_map()->full_map_file = malloc(sizeof(char *) * _map()->line_count);
	if (!_map()->full_map_file)
	{
		get_next_line(-1);
		exit(error_print("malloc fail [extract_map_file()]", 0));
	}
	close(_map()->full_map_file_fd);
	_map()->map_fd = open(_map()->map_name, O_RDONLY);
	i = 0;
	while (i < _map()->line_count)
		_map()->full_map_file[i++] = get_next_line(_map()->map_fd);
	get_next_line(-1);
}

/* Analyse each line int the map file. If we get to a line that is part of the map,
 * we check that all necessary parameters have been set. If so, we store a pointer to
 * the first line of the map and close the map by setting the first line that starts
 * with a newline to NULL. */
void	process_map_file_contents()
{
	int	i;
	int	started_reading_map;

	started_reading_map = 0;
	i = -1;
	while (_map()->full_map_file[++i])
	{
		// if line is part of map
		if (line_is_in_map(_map()->full_map_file[i]))
			// if it's the first line found and all parameters have been found
			if (!started_reading_map++ && all_map_params_are_set())
				// store pointer to that first line
				_map()->map = _map()->full_map_file[i];
		else if (started_reading_map && _map()->full_map_file[i][0] == '\n')
		{
			free(_map()->full_map_file[i]);
			_map()->full_map_file[i] = NULL;
			break ;
		}
		else
			if (!check_for_texture(_map()->full_map_file[i]))
				check_for_colors(_map()->full_map_file[i]);
	}
}
