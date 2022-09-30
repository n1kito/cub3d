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

	// sprite_size = _map()->sprite_size;
	if (is_path_directory(args[1]))
		ft_exit("one of the textures is a directory", 1);
	// sprite = mlx_xpm_file_to_image(_map()->graphics->mlx_ptr, args[1],
		// &sprite_size, &sprite_size);
	sprite = args[1]; // remove to work with mlx
	if (!sprite)
		ft_exit("texture file open failed", 1);
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
		ft_exit("north wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "SO") == 0 && _map()->params->s_texture)
		ft_exit("south wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "EA") == 0 && _map()->params->e_texture)
		ft_exit("east wall texture defined twice", 1);
	else if (ft_strcmp(args[0], "WE") == 0 && _map()->params->w_texture)
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
