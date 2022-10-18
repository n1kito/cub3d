//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

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
		ft_exit("malloc error in check_for_texture()", 1);
	if (ft_strcmp(split[0], "NO") == 0
		|| ft_strcmp(split[0], "SO") == 0
		|| ft_strcmp(split[0], "EA") == 0
		|| ft_strcmp(split[0], "WE") == 0)
		check_and_store_path(split);
	ft_freetab(&split);
}

/* Checks that texture path is not a directory and tries to open it.
 * Fails if there was already a texture defined for that orientation
 * or texture cannot be opened. */
void	check_and_store_path(char **args)
{
	// int		sprite_size;
	void	*sprite;
	int		sprite_width;
	int		sprite_height;

	// sprite_size = _map()->sprite_size;
	if (is_path_directory(args[1]))
		ft_exit("one of the textures is a directory", 1);
	// sprite = mlx_xpm_file_to_image(_map()->graphics->mlx_ptr, args[1],
		// &sprite_size, &sprite_size);
	if (!_map()->graphics->mlx_ptr)
		ft_exit("there is no mlx_ptr\n", 1);
	if (args[1][ft_strlen(args[1]) - 1] == '\n')
		args[1][ft_strlen(args[1]) - 1] = '\0';
	sprite = mlx_xpm_file_to_image(_map()->graphics->mlx_ptr, args[1], &sprite_width, &sprite_height);
	if (!sprite)
		ft_exit("texture file open failed", 1);
	// if (sprite_width != sprite_height)
	// 	ft_exit("sprite is not a square", 1);
	check_for_double_textures(args);
	if (ft_strcmp(args[0], "NO") == 0)
	{
		_map()->params->n_texture.image = sprite;
		_map()->params->n_texture.sprite_size = sprite_width;
		_map()->params->n_texture.addr = mlx_get_data_addr(_map()->params->n_texture.image, &_map()->params->n_texture.bpp, &_map()->params->n_texture.line_length, &_map()->params->n_texture.endian);
	}
	else if (ft_strcmp(args[0], "SO") == 0)
	{
		_map()->params->s_texture.image = sprite;
		_map()->params->s_texture.sprite_size = sprite_width;
		_map()->params->s_texture.addr = mlx_get_data_addr(_map()->params->s_texture.image, &_map()->params->s_texture.bpp, &_map()->params->s_texture.line_length, &_map()->params->s_texture.endian);
	}
	else if (ft_strcmp(args[0], "EA") == 0)
	{
		_map()->params->e_texture.image = sprite;
		_map()->params->e_texture.sprite_size = sprite_width;
		_map()->params->e_texture.addr = mlx_get_data_addr(_map()->params->e_texture.image, &_map()->params->e_texture.bpp, &_map()->params->e_texture.line_length, &_map()->params->e_texture.endian);
	}
	else if (ft_strcmp(args[0], "WE") == 0)
	{
		_map()->params->w_texture.image = sprite;
		_map()->params->w_texture.sprite_size = sprite_width;
		_map()->params->w_texture.addr = mlx_get_data_addr(_map()->params->w_texture.image, &_map()->params->w_texture.bpp, &_map()->params->w_texture.line_length, &_map()->params->w_texture.endian);
	}
}

/* Exits if the texture pointer was already assigned. */
void	check_for_double_textures(char **args)
{
	if (ft_strcmp(args[0], "NO") == 0 && _map()->params->n_texture.image)
		ft_exit("north wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "SO") == 0 && _map()->params->s_texture.image)
		ft_exit("south wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "EA") == 0 && _map()->params->e_texture.image)
		ft_exit("east wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "WE") == 0 && _map()->params->w_texture.image)
		ft_exit("east wall texture defined twice", 1);
}

/* Returns 1 if path tested is a directory. */
int	is_path_directory(char *path)
{
	int		dir_test;

	dir_test = open(path, O_DIRECTORY);
	if (dir_test != -1)
	{
		close(dir_test);
		return (1);
	}
	return (0);
}
