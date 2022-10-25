/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:22 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:50:26 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Analyses a line extracted from the .cub file and checks if the first cell
 * is a texture identifier. If a texture identifier is found, the corresponding
 * path is tested and stored if the texture was successfully opened . */
void	check_for_texture(char *line)
{
	char	**split;

	if (!line || line[0] == '\n')
		return ;
	split = ft_split(line, ' ');
	if (!split)
		ft_exit("malloc fail [check_for_texture()]", 1);
	if (ft_strcmp(split[0], "NO") == 0
		|| ft_strcmp(split[0], "SO") == 0
		|| ft_strcmp(split[0], "EA") == 0
		|| ft_strcmp(split[0], "WE") == 0)
		check_and_store_path(split);
	ft_freetab(&split);
}

/* Checks that texture path is not a directory and tries to open it.
 * Fails and exits if there was already a texture defined for that orientation
 * or texture cannot be opened. */
void	check_and_store_path(char **args)
{
	if (args[1][ft_strlen(args[1]) - 1] == '\n')
		args[1][ft_strlen(args[1]) - 1] = '\0';
	if (!file_has_extension(args[1], ".xpm"))
	{
		ft_freetab(&args);
		ft_exit("textures require .xpm files", 1);
	}
	if (is_path_directory(args[1]))
	{
		ft_freetab(&args);
		ft_exit("one of the textures is a directory", 1);
	}
	check_for_double_textures(args);
	if (ft_strcmp(args[0], "NO") == 0)
		_map()->params->n_texture.path = ft_strdup(args[1]);
	else if (ft_strcmp(args[0], "SO") == 0)
		_map()->params->s_texture.path = ft_strdup(args[1]);
	else if (ft_strcmp(args[0], "EA") == 0)
		_map()->params->e_texture.path = ft_strdup(args[1]);
	else if (ft_strcmp(args[0], "WE") == 0)
		_map()->params->w_texture.path = ft_strdup(args[1]);
}

/* Exits if the texture path pointer was already assigned. */
void	check_for_double_textures(char **args)
{
	if (ft_strcmp(args[0], "NO") == 0 && _map()->params->n_texture.path)
	{
		ft_freetab(&args);
		ft_exit("north wall texture defined twice", 1);
	}
	else if (ft_strcmp(args[0], "SO") == 0 && _map()->params->s_texture.path)
	{
		ft_freetab(&args);
		ft_exit("south wall texture defined twice", 1);
	}
	else if (ft_strcmp(args[0], "EA") == 0 && _map()->params->e_texture.path)
	{
		ft_freetab(&args);
		ft_exit("east wall texture defined twice", 1);
	}
	else if (ft_strcmp(args[0], "WE") == 0 && _map()->params->w_texture.path)
	{
		ft_freetab(&args);
		ft_exit("west wall texture defined twice", 1);
	}
}

/* Uses mlx_get_data_addr to assign texture parameters to the corresponding
 * structure. */
void	assign_texture_parameters(t_img *texture, int sprite_size)
{
	texture->sprite_size = sprite_size;
	texture->addr = mlx_get_data_addr(texture->image, &texture->bpp,
			&texture->line_length, &texture->endian);
}
