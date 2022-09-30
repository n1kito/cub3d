#include "cub3D.h"

/* Analyses a line extracted from the .cub file and checks if the first cell is a texture identifier.
 * If a texture identifier is found, the corresponding path is tested and stored the texture was successfully
 * opened . */
int	check_for_texture(char *line)
{
	char	**split_line;

	if (!line || line[0] == '\n')
		return (1);
	split_line = ft_split(line, ' ');
	if (!split_line)
		exit(error_print("malloc error in check_for_texture()", 1));
	if (!split_line[1] || split_line[2])
	{
		ft_freetab(split_line);
		exit(error_print("map parameter line has too few or too many elements", 1));
	}
	if (ft_strcmp(split_line[0], "NO") == 0 || ft_strcmp(split_line[0], "SO") == 0
		|| ft_strcmp(split_line[0], "EA") == 0 || ft_strcmp(split_line[0], "WE") == 0)
	{
		check_and_store_path(split_line);
		return (ft_freetab(split_line), 1);
	}
	return (ft_freetab(split_line), 0);
}

/* Checks that texture path is not a directory and tries to open it.
 * Fails if there was already a texture defined for that orientation
 * or texture cannot be opened. */
void	check_and_store_path(char **args)
{
	//int		sprite_size;
	void	*sprite;

	//sprite_size = _map()->sprite_size;
	if (is_path_directory(args[1]))
		exit(error_print("one of the textures is a directory", 1));
	//sprite = mlx_xpm_file_to_image(_map()->graphics->mlx_ptr, args[1],
	//	sprite_size, sprite_size);
	sprite = args[0];
	if (!sprite)
		exit(error_print("texture file open failed", 1));
	check_for_double_textures(args);
	if (ft_strcmp(args[0], "NO") == 0)	
		_map()->params->n_texture = sprite;
	else if (ft_strcmp(args[0], "SO") == 0)
		_map()->params->s_texture = sprite;
	else if (ft_strcmp(args[0], "EA") == 0)
		_map()->params->e_texture = sprite;
	else if (ft_strcmp(args[0], "WE") == 0)
		_map()->params->w_texture = sprite;
}

/* Exits if the texture pointer was already assigned. */
void	check_for_double_textures(char **args)
{
	if (ft_strcmp(args[0], "NO") == 0 && _map()->params->n_texture)
		exit(error_print("north wall texture defined twice", 1));
	else if (ft_strcmp(args[0], "SO") == 0 && _map()->params->s_texture)
		exit(error_print("south wall texture defined twice", 1));
	else if (ft_strcmp(args[0], "EA") == 0 && _map()->params->e_texture)
		exit(error_print("east wall texture defined twice", 1));
	else if (ft_strcmp(args[0], "WE") == 0 && _map()->params->w_texture)
		exit(error_print("east wall texture defined twice", 1));
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
