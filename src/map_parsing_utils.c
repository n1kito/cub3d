/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:20 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 16:35:27 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int	i;

	i = 0;
	while (line[i] == 32)
	{
		if (line[i] != 32)
			break ;
		i++;
	}
	if ((line[i] == 'F' && line[i + 1] == ' ')
		|| (line[i] == 'C' && line[i + 1] == ' ')
		|| (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		|| (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		|| (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		|| (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' '))
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
