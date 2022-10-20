//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Frees texture path and destroys image, if they exist. */
void	free_texture(t_img *texture)
{
	if (texture->path)
		free(texture->path);
	if (texture->image)
		mlx_destroy_image(_map()->graphics->mlx_ptr, texture->image);
}

/* Frees every allocated memory space. */
void	free_all(void)
{
	t_mlx		*g;
	t_params	*p;

	g = _map()->graphics;
	p = _map()->params;
	free_texture(&p->n_texture);
	free_texture(&p->e_texture);
	free_texture(&p->s_texture);
	free_texture(&p->w_texture);
	if (g->minimap_img.image)
		mlx_destroy_image(g->mlx_ptr, g->minimap_img.image);
	if (g->game_img.image)
		mlx_destroy_image(g->mlx_ptr, g->game_img.image);
	if (_map()->is_minimap_open)
		mlx_destroy_window(g->mlx_ptr, g->minimap_window_ptr);
	if (g->window_ptr)
		mlx_destroy_window(g->mlx_ptr, g->window_ptr);
	if (g->mlx_ptr)
		mlx_destroy_display(g->mlx_ptr);
	free(g->mlx_ptr);
	free(p);
	ft_freetab(&_map()->file_contents);
	free(g);
	free(_map());
}
