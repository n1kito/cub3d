//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

int	error_print(char *error, int return_value)
{
	static int	is_first_error = 0;

	if (is_first_error++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (return_value);
}

int	exit_game(void)
{
	ft_exit(NULL, 0);
	exit(0);
}

void	ft_exit(char *error, int exit_code)
{
	if (error)
		error_print(error, 0);
	free_all();
	exit(exit_code);
}

void	free_all(void)
{
	t_mlx		*g;
	t_params	*p;

	g = _map()->graphics;
	p = _map()->params;
	if (p->e_texture.path)
		free(p->e_texture.path);
	if (p->s_texture.path)
		free(p->s_texture.path);
	if (p->n_texture.path)
		free(p->n_texture.path);
	if (p->w_texture.path)
		free(p->w_texture.path);
	if (p->e_texture.image)
		mlx_destroy_image(g->mlx_ptr, p->e_texture.image);
	if (p->w_texture.image)
		mlx_destroy_image(g->mlx_ptr, p->w_texture.image);
	if (p->n_texture.image)
		mlx_destroy_image(g->mlx_ptr, p->n_texture.image);
	if (p->s_texture.image)
		mlx_destroy_image(g->mlx_ptr, p->s_texture.image);
	if (g->minimap_img.image)
		mlx_destroy_image(g->mlx_ptr, g->minimap_img.image);
	if (g->game_img.image)
		mlx_destroy_image(g->mlx_ptr, g->game_img.image);
	if (_map()->is_minimap_open)
		mlx_destroy_window(g->mlx_ptr, g->minimap_window_ptr);
	if (g->window_ptr)
		mlx_destroy_window(g->mlx_ptr, g->window_ptr);
	free(p);
	ft_freetab(&_map()->file_contents);
	if (g->mlx_ptr)
		mlx_destroy_display(g->mlx_ptr);
	free(g->mlx_ptr);
	free(g);
	free(_map());
}

/* Returns an int containing the RGB color values passed as parameter. */
int	color_generator(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
