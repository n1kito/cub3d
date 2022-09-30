#include "cub3D.h"

/* 
	Checker si c'est bien un C ou un F, et que yen a bien qu'un seul
	Checker si les chiffres sont pas en dessous/dessus de 0/255
	Si ya 3 color values 
*/

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
			{
				printf("value: %s\n", splitted_line[i]);
				exit(error_print("Color values are wrong.", 1));
			}
		i++;
	}
	// TODO freetab
}

void	init_map_colors(char **line)
{
	char	**numbers;

	numbers = ft_split(line[1], ',');
	if (line[0][0] == 'F')
	{
		_map()->params->f_color[0] = ft_atoi(numbers[0]);
		_map()->params->f_color[1] = ft_atoi(numbers[1]);
		_map()->params->f_color[2] = ft_atoi(numbers[2]);
	}
	else
	{
		_map()->params->c_color[0] = ft_atoi(numbers[0]);
		_map()->params->c_color[1] = ft_atoi(numbers[1]);
		_map()->params->c_color[2] = ft_atoi(numbers[2]);
	}
	ft_freetab(numbers);
	ft_freetab(line);
}

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
		// exit(error_print("Arg is too long.", 1));
	if (splitted_line[0][0] && (splitted_line[0][0] != 'C' && splitted_line[0][0] != 'F'))
		return (0);
	check_color_values(splitted_line[1]);
	init_map_colors(splitted_line);
	return (1);
}


void	map_name_checker()
{
	int	i;

	i = 0;
	while (_map()->map_name[i])
	{
		if (i == 0 && _map()->map_name[i] == '.' && _map()->map_name[1] == '/')
			i += 2;
		else if (_map()->map_name[i] == '.')
		{
			if (ft_strncmp(_map()->map_name + i + 1, "cub", ft_strlen("cub")) == 0)
				if (_map()->map_name[i + ft_strlen("cub") + 1] == '\0')
					return ;
					//return (1);
			i++;
		}
		else
			i++;
	}
	exit(error_print("wrong map name", 1));
}

/* */

int	map_file_checker()
{
	int	dir_test;

	map_name_checker();
	dir_test = open(_map()->map_name, O_DIRECTORY);
	if (dir_test != -1)
		exit(error_print("map argument is a directory", 1));
	close(dir_test);
	_map()->map_fd = open(_map()->map_name, O_RDONLY);
	if (_map()->map_fd == -1)
		exit(error_print("map file could not be opened", 1));
	return (0);
}
