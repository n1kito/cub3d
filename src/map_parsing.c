/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:15 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 15:45:06 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Analyses map file and exits in case of error,
 * or if all parameters are not correct. */
void	map_parsing(void)
{
	get_file_dimensions();
	extract_map_file();
	process_map_file_contents();
	if (!_map()->map)
		ft_exit("map not found", 1);
	closed_map_check();
	if (_map()->params->pl_start_pos[0] == -1)
		ft_exit("missing player starting position", 1);
	get_map_dimensions();
	map_last_in_file_check();
}

/* Saves the map to a char** in my structure, and calls get_next_line() one
 * last time to clear the buffer and avoid leaks. */
void	extract_map_file(void)
{
	int	i;
	int	*map_fd_tmp;

	map_fd_tmp = &_map()->map_fd;
	_map()->file_contents = malloc(sizeof(char *)
		* (_map()->file_line_count + 1));
	if (!_map()->file_contents)
	{
		get_next_line(-1);
		ft_exit("malloc fail [extract_map_file()]", 0);
	}
	close(*map_fd_tmp);
	*map_fd_tmp = open(_map()->map_name, O_RDONLY);
	i = 0;
	while (i < _map()->file_line_count)
		_map()->file_contents[i++] = get_next_line(*map_fd_tmp);
	_map()->file_contents[i] = NULL;
	get_next_line(-1);
	close(*map_fd_tmp);
}

/* Returns 1 if all necessary parameters (textures and colors) have been set.
 * Exits if one of them is missing. */
int	all_map_params_are_set(void)
{
	t_params	*p;

	p = _map()->params;
	if (!p->n_texture.path
		|| !p->s_texture.path
		|| !p->e_texture.path
		|| !p->w_texture.path)
		ft_exit("missing texture parameter(s) in map file", 1);
	if (_map()->params->c_rgb_color[0] == -1)
		ft_exit("missing ceiling color parameter in map file", 1);
	if (_map()->params->f_rgb_color[0] == -1)
		ft_exit("missing floor color parameter in map file", 1);
	return (1);
}

/* Checks that the line has one of the required parameters and that it does
 * not have extra items in the line. */
int	correct_parameter_type(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		ft_exit("malloc fail [correct_parameter_type()]", 1);
	if (split[0] && split[0][0] == '\n')
		return (ft_freetab(&split), 1);
	if (ft_tabsize(split) < 2
		|| (ft_tabsize(split) > 2
			&& split[2][0] != '\n'))
	{
		ft_freetab(&split);
		ft_exit("map parameter line has too few/many elements", 1);
	}
	if ((ft_strlen(split[0]) == 1
			&& (split[0][0] == 'C'
			|| split[0][0] == 'F'))
		|| (ft_strlen(split[0]) == 2
			&& (ft_strcmp(split[0], "NO") == 0
				|| ft_strcmp(split[0], "SO") == 0
				|| ft_strcmp(split[0], "EA") == 0
				|| ft_strcmp(split[0], "WE") == 0)))
		return (ft_freetab(&split), 1);
	ft_freetab(&split);
	return (ft_exit("wrong argument type", 1), 0);
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
		if (!line_contains_parameter(_map()->file_contents[i])
			&& _map()->file_contents[i][0] != '\n')
		{
			if (!started_reading_map++ && all_map_params_are_set())
				_map()->map = _map()->file_contents + i;
			check_map_line(_map()->file_contents[i], started_reading_map);
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
