/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:51 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 11:05:32 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Frees texture path and destroys image, if they exist. */
void	free_text(t_img *txt1, t_img *txt2, t_img *txt3, t_img *txt4)
{
	if (txt1->path)
		free(txt1->path);
	if (txt1->image)
		mlx_destroy_image(_map()->graphics->mlx_ptr, txt1->image);
	if (txt2->path)
		free(txt2->path);
	if (txt2->image)
		mlx_destroy_image(_map()->graphics->mlx_ptr, txt2->image);
	if (txt3->path)
		free(txt3->path);
	if (txt3->image)
		mlx_destroy_image(_map()->graphics->mlx_ptr, txt3->image);
	if (txt4->path)
		free(txt4->path);
	if (txt4->image)
		mlx_destroy_image(_map()->graphics->mlx_ptr, txt4->image);
}

/* Frees every allocated memory space. */
void	free_all(void)
{
	t_mlx		*g;
	t_params	*p;

	g = _map()->graphics;
	p = _map()->params;
	if (p)
		free_text(&p->n_texture, &p->e_texture, &p->s_texture, &p->w_texture);
	if (g && g->minimap_img.image)
		mlx_destroy_image(g->mlx_ptr, g->minimap_img.image);
	if (g && g->game_img.image)
		mlx_destroy_image(g->mlx_ptr, g->game_img.image);
	if (_map()->is_minimap_open)
		mlx_destroy_window(g->mlx_ptr, g->minimap_window_ptr);
	if (g && g->window_ptr)
		mlx_destroy_window(g->mlx_ptr, g->window_ptr);
	if (g && g->mlx_ptr)
		mlx_destroy_display(g->mlx_ptr);
	if (g)
		free(g->mlx_ptr);
	free(p);
	ft_freetab(&_map()->file_contents);
	free(g);
	if (_map()->map_fd >= 0)
		close(_map()->map_fd);
	free(_map());
}
