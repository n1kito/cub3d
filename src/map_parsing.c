#include "cub3D.h"

/* Analyses map file and exits in case of error, or if all parameters are not correct. */
void	map_parsing(void)
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
	// TODO:
	// check_map_contents();
}

/* Saves the map to a char** in my structure, and calls get_next_line() one
 * last time to clear the buffer and avoid leaks. */
void	extract_map_file(void)
{
	int	i;
	int	*map_fd_tmp;

	map_fd_tmp = &_map()->map_fd;
	_map()->file_contents = malloc(sizeof(char *) * _map()->file_line_count);
	if (!_map()->file_contents)
	{
		get_next_line(-1);
		exit(error_print("malloc fail [extract_map_file()]", 0));
	}
	close(*map_fd_tmp);
	*map_fd_tmp = open(_map()->map_name, O_RDONLY);
	i = 0;
	while (i < _map()->file_line_count)
		_map()->file_contents[i++] = get_next_line(*map_fd_tmp);
	_map()->file_contents[i] = NULL;
	get_next_line(-1);
}

/* Returns 1 if all necessary parameters (textures and colors) have been set.
 * Exits if one of them is missing. */
int	all_map_params_are_set(void)
{
	t_params	*p;

	p = _map()->params;
	if (!p->n_texture || !p->s_texture || !p->e_texture || !p->w_texture)
		exit(error_print("missing texture parameter(s) in map file", 1));
	if (_map()->params->c_color[0] == -1)
		exit(error_print("missing ceiling color parameter in map file", 1));
	if (_map()->params->f_color[0] == -1)
		exit(error_print("missing floor color parameter in map file", 1));
	return (1);
}

/* Checks that the line has one of the required parameters and that it does
 * not have extra items in the line. */
int	correct_parameter_type(char *line)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		exit(error_print("malloc fail [correct_parameter_type()]", 1));
	if (splitted_line[0] && splitted_line[0][0] == '\n')
		return (1);
	if (ft_tabsize(splitted_line) < 2
		|| (ft_tabsize(splitted_line) > 2
			&& splitted_line[2][0] != '\n'))
	{
		ft_freetab(splitted_line);
		exit(error_print("map parameter line has too few/many elements", 1));
	}
	if ((ft_strlen(splitted_line[0]) == 1
			&& (splitted_line[0][0] == 'C'
			|| splitted_line[0][0] == 'F'))
		|| (ft_strlen(splitted_line[0]) == 2
			&& (ft_strcmp(splitted_line[0], "NO") == 0
				|| ft_strcmp(splitted_line[0], "SO") == 0
				|| ft_strcmp(splitted_line[0], "EA") == 0
				|| ft_strcmp(splitted_line[0], "WE") == 0)))
		return (1);
	exit(error_print("wrong argument type", 1));
}

/* Analyse each line int the map file.
 * If we get to a line that is part of the map, we check that all
 * necessary parameters have been set. If so, we store a pointer to the
 * first line of the map and close the map by setting the first line that starts
 * with a newline to NULL. */
void	process_map_file_contents(void)
{
	int	i;
	int	started_reading_map;

	started_reading_map = 0;
	i = -1;
	while (_map()->file_contents[++i])
	{
		if (line_is_part_of_map(_map()->file_contents[i]))
		{
			if (!started_reading_map++ && all_map_params_are_set())
				_map()->map = _map()->file_contents + i;
		}
		else if (started_reading_map && _map()->file_contents[i][0] == '\n')
		{
			free(_map()->file_contents[i]);
			_map()->file_contents[i] = NULL;
			break ;
		}
		else
			if (correct_parameter_type(_map()->file_contents[i]))
				if (!check_for_colors(_map()->file_contents[i]))
					check_for_texture(_map()->file_contents[i]);
	}
}
