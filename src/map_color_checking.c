#include "cub3D.h"

/* Checks the given string has actual digits, 3 of them, not over 255 / below 0
 * If any is wrong, will exit with a message on stderr. */
void	check_color_values(char *line)
{
	int		i;
	char **splitted_line;

	splitted_line = ft_split(line, ',');
	i = 0;
	while (splitted_line[i])
	{
		if (splitted_line[i][ft_strlen(splitted_line[i]) - 1] == '\n')
			splitted_line[i][ft_strlen(splitted_line[i]) - 1] = '\0';
		if (i >= 3)
			exit(error_print("Too much color values.", 1));
		if (ft_strlen(splitted_line[i]) == 0
			|| (ft_strlen(splitted_line[i]) > 3)
			|| !ft_string_is_digit(splitted_line[i])
			|| atoi(splitted_line[i]) > 255
			|| atoi(splitted_line[i]) < 0)
				exit(error_print("Color values are wrong.", 1));
		i++;
	}
	// TODO freetab
}

/* Checks if a F or C is set twice, if not, assigns each values to
 * an int array that will be the RGB value for the floor and ceiling */
void	init_map_colors(char **line)
{
	char	**numbers;

	numbers = ft_split(line[1], ',');
	if (line[0][0] == 'F')
	{
		if (_map()->params->f_color[0] != -1)
			exit(error_print("floor color set twice", 1));
		_map()->params->f_color[0] = ft_atoi(numbers[0]);
		_map()->params->f_color[1] = ft_atoi(numbers[1]);
		_map()->params->f_color[2] = ft_atoi(numbers[2]);
	}
	else
	{
		if (_map()->params->c_color[0] != -1)
			exit(error_print("ceiling color set twice", 1));
		_map()->params->c_color[0] = ft_atoi(numbers[0]);
		_map()->params->c_color[1] = ft_atoi(numbers[1]);
		_map()->params->c_color[2] = ft_atoi(numbers[2]);
	}
	ft_freetab(numbers);
	ft_freetab(line);
}

/* Beginning of the checking of the color values (full checking
 * in the two functions above). */
int	check_for_colors(char *line)
{
	char	**splitted_line;

	if (line[0] == '\n' && ft_strlen(line) == 1)
		return (1);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		exit(error_print("Malloc Error", 1));
	if (ft_strlen(splitted_line[0]) != 1)
		return (0);
	if (splitted_line[0][0] && (splitted_line[0][0] != 'C' && splitted_line[0][0] != 'F'))
		return (0);
	check_color_values(splitted_line[1]);
	init_map_colors(splitted_line);
	return (1);
}