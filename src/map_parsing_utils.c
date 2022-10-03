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

// /* Checks that line only contains parameters that could be part of the map. */
// int	line_is_part_of_map(char *line)
// {
// 	int	i;

// 	if (!line || line[0] == '\n')
// 		return (0);
// 	i = -1;
// 	while (line[++i])
// 		if (!is_map_character(line[i]))
// 			if (!(line[i] == '\n' && line[i + 1] == '\0'))
// 				return (0);
// 	return (1);
// }

/* Checks that line contains the idenfifier of a parameter. */
int	line_contains_parameter(char *line)
{
	if ((line[0] == 'F' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		|| (line[0] == 'W' && line[1] == 'E' && line[2] == ' '))
		return (1);
	return (0);
}

/* Checks that the map line has only authorized characters.
 * If the character is a player starting position indicator and
 * none has been logged before, coordinates are logged.
 * Otherwise, the program exits. */
void	check_map_line(char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (!is_map_character(line[j]))
			ft_exit("map has forbidden character", 1);
		else if (is_start_position(line[j]))
		{	
			if (_map()->params->pl_start_pos[0] != -1)
				ft_exit("map has too many starting positions", 1);
			_map()->params->pl_start_pos[0] = i - 1;
			_map()->params->pl_start_pos[1] = j;
		}
		j++;
	}
}

/* Checks that the char corresponds to a starting position token. */
int	is_start_position(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}