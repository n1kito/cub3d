#include "cub3D.h"

/* 
	Checker si c'est bien un C ou un F, et que yen a bien qu'un seul
	Checker si les chiffres sont pas en dessous/dessus de 0/255
	Si ya 3 color values 
*/

int	check_color_values(char *line)
{
	int		i;
	char **splitted_line;

	splitted_line = ft_split(line, ',');
	i = 0;
	while (splitted_line[i])
	{
		if (i >= 3)
			exit(error_print("Too much color values.", 1));
		if (ft_strlen(splitted_line[i]) != 3 || !ft_string_is_digit(splitted_line[i]) || atoi(splitted_line[i]) > 255 || atoi(splitted_line[i]) < 0)
			exit(error_print("Color values are wrong.", 1));
		i++;
	}
	return (1);
}

int	check_for_colors(char *line)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		exit(error_print("Malloc Error", 1));
	if (ft_strlen(splitted_line[0]) != 1)
		exit(error_print("Arg is too long.", 1));
	if (splitted_line[0][0] && (splitted_line[0][0] != 'C' || splitted_line[0][0] != 'F'))
		exit(error_print("Not E or F.", 1));
	if (check_color_values(splitted_line[1]))
		exit(error_print("Color values are wrong.", 1));
	// TODO : Faire fonction qui met les valeurs de map.
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
					return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

/* */

int	map_checker()
{
	int	dir_test;

	map_name_checker();
	dir_test = open(_map()->map_name, O_DIRECTORY);
	if (dir_test != -1)
		exit(error_print("Map argument is a directory", 1));
	// TODO close the fd if open was actually a directory? 
	_map()->map_fd = open(_map()->map_name, O_RDONLY);
	if (_map()->map_fd == -1)
		exit(error_print("Map file could not be opened", 1));
	return (0);
}