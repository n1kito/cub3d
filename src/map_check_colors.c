/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:26 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:50:16 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Checks the given string has actual digits, 3 of them, not over 255 / below 0
 * If any is wrong, will exit with a message on stderr. */
void	check_color_values(char **line)
{
	int		i;
	char	**splitted_line;

	splitted_line = ft_split(line[1], ',');
	if (ft_tabsize(splitted_line) != 3)
	{
		multi_freetab(&line, &splitted_line);
		ft_exit("color has too few/many values", 1);
	}
	i = -1;
	while (splitted_line[++i])
	{
		if (splitted_line[i][ft_strlen(splitted_line[i]) - 1] == '\n')
			splitted_line[i][ft_strlen(splitted_line[i]) - 1] = '\0';
		if (ft_strlen(splitted_line[i]) == 0 || ft_strlen(splitted_line[i]) > 3
			|| !ft_string_is_digit(splitted_line[i])
			|| ft_atoi(splitted_line[i]) > 255 || ft_atoi(splitted_line[i]) < 0)
		{
			multi_freetab(&line, &splitted_line);
			ft_exit("color values are wrong", 1);
		}
	}
	ft_freetab(&splitted_line);
}

/* Checks if F or C is set twice, if not, assigns each values to
 * an int array that will be the RGB value for the floor and ceiling */
void	init_map_colors(char **line)
{
	char	**numbers;

	numbers = ft_split(line[1], ',');
	if ((line[0][0] == 'F' && _map()->params->f_rgb_color[0] != -1)
		|| (line[0][0] == 'C' && _map()->params->c_rgb_color[0] != -1))
	{
		multi_freetab(&line, &numbers);
		ft_exit("color set twice", 1);
	}
	if (line[0][0] == 'F')
	{
		_map()->params->f_rgb_color[0] = ft_atoi(numbers[0]);
		_map()->params->f_rgb_color[1] = ft_atoi(numbers[1]);
		_map()->params->f_rgb_color[2] = ft_atoi(numbers[2]);
		assign_color(&_map()->params->f_color, _map()->params->f_rgb_color);
	}
	else
	{
		_map()->params->c_rgb_color[0] = ft_atoi(numbers[0]);
		_map()->params->c_rgb_color[1] = ft_atoi(numbers[1]);
		_map()->params->c_rgb_color[2] = ft_atoi(numbers[2]);
		assign_color(&_map()->params->c_color, _map()->params->c_rgb_color);
	}
	ft_freetab(&numbers);
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
		ft_exit("malloc fail [check_for_colors()]", 1);
	if (ft_strlen(splitted_line[0]) != 1)
		return (ft_freetab(&splitted_line), 0);
	if (splitted_line[0][0] && (splitted_line[0][0] != 'C'
		&& splitted_line[0][0] != 'F'))
		return (ft_freetab(&splitted_line), 0);
	check_color_values(splitted_line);
	init_map_colors(splitted_line);
	return (ft_freetab(&splitted_line), 1);
}

/* Uses freetab() on two tabs. */
void	multi_freetab(char ***tab1, char ***tab2)
{
	ft_freetab(tab1);
	ft_freetab(tab2);
}
