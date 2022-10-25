/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:24 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:14:33 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Checks if a filename map ends with particular extension. */
int	file_has_extension(char *filename, char *extension)
{
	int	i;
	int	extension_len;

	extension_len = ft_strlen(extension);
	i = ft_strlen(filename);
	if (i < extension_len + 1)
		return (0);
	i -= extension_len;
	if (ft_strncmp(&filename[i], extension, extension_len) == 0)
		return (1);
	return (0);
}

/* Checks the filename, file type and permissions on map file. */
int	map_file_checker(void)
{
	int	dir_test;
	int	*map_fd_tmp;

	map_fd_tmp = &_map()->map_fd;
	if (!file_has_extension(_map()->map_name, ".cub"))
		ft_exit("map requires .cub extension", 1);
	dir_test = open(_map()->map_name, O_DIRECTORY);
	if (dir_test != -1)
	{
		close(dir_test);
		ft_exit("map argument is a directory", 1);
	}
	*map_fd_tmp = open(_map()->map_name, O_RDONLY);
	if (*map_fd_tmp == -1)
		ft_exit("map file could not be opened", 1);
	return (0);
}
