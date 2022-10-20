//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Checks whether the tested char is an accepted map character or not. */
int	is_map_character(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

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

/* Turns the player's original angle depending on the map player parameter. */
void	set_player_start_angle(char player_char)
{
	if (player_char == 'N')
		_map()->plyr.rot_angle = PI * 1.5;
	else if (player_char == 'E')
		_map()->plyr.rot_angle = 0;
	else if (player_char == 'S')
		_map()->plyr.rot_angle = PI * 0.5;
	else if (player_char == 'W')
		_map()->plyr.rot_angle = PI;
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
			_map()->params->pl_start_pos[0] = j;
			_map()->params->pl_start_pos[1] = i - 1;
			set_player_start_angle(line[j]);
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
