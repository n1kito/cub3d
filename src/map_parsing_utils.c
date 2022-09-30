#include "cub3D.h"

/* Measures the number of lines and columns in the map and saves them in the
 * map structure. */
void	get_map_dimensions(void)
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

/* Checks whether the tested char is an accepted map character or not. */
int	is_map_character(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/* Checks that line only contains parameters that could be part of the map. */
int	line_is_part_of_map(char *line)
{
	int	i;

	if (!line || line[0] == '\n')
		return (0);
	i = -1;
	while (line[++i])
		if (!is_map_character(line[i]))
			if (!(line[i] == '\n' && line[i + 1] == '\0'))
				return (0);
	return (1);
}
