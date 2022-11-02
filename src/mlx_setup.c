/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:06 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 13:24:02 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Sets up all requires mlx elements. */
void	mlx_setup(void)
{
	t_map	*m;
	t_mlx	*g;

	m = _map();
	g = m->graphics;
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		ft_exit("mlx_init() fail [mlx_setup()]", 1);
	open_all_textures();
	g->window_ptr = mlx_new_window(g->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, m->map_name);
	if (!g->window_ptr)
		ft_exit("failed to create window [mlx_setup()]", 1);
	g->minimap_img.image = mlx_new_image(g->mlx_ptr,
			g->minimap_width, g->minimap_height);
	g->game_img.image = mlx_new_image(g->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->game_img.image || !g->minimap_img.image)
		ft_exit("failed to create images", 1);
}

/* Update routine for both main game window and minimap window. */
int	update_window(void)
{
	t_mlx	*g;

	g = _map()->graphics;
	move_player(&_map()->plyr);
	cast_all_rays();
	generate_projection();
	mlx_put_image_to_window(g->mlx_ptr, g->window_ptr, g->game_img.image, 0, 0);
	mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 20, WHITE, "(m) minimap");
	if (_map()->plyr.mode_dell)
		mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 35, WHITE, "(f) go fast");
	else
		mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 35, WHITE, "(f) go slow");
	mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 50, WHITE, "(q) quit");
	if (_map()->is_minimap_open)
	{
		render_minimap(_map()->graphics, _map()->map);
		mlx_clear_window(g->mlx_ptr, g->minimap_window_ptr);
		mlx_put_image_to_window(g->mlx_ptr, g->minimap_window_ptr,
			g->minimap_img.image,
			(g->minimap_width - 3 * MINI_TILE) / 2 - g->minimap_dot_pos[0],
			(g->minimap_height - 3 * MINI_TILE) / 2 - g->minimap_dot_pos[1]);
	}
	return (0);
}

/* Initializes key hooks for main game window. */
void	init_hooks(void)
{
	t_mlx		*g;
	t_params	*p;

	g = _map()->graphics;
	p = _map()->params;
	_map()->plyr.x = (p->pl_start_pos[0] * TILE_SIZE) + (TILE_SIZE / 2);
	_map()->plyr.y = (p->pl_start_pos[1] * TILE_SIZE) + (TILE_SIZE / 2);
	g->minimap_img.addr = mlx_get_data_addr(g->minimap_img.image,
			&g->minimap_img.bpp, &g->minimap_img.line_length,
			&g->minimap_img.endian);
	g->game_img.addr = mlx_get_data_addr(g->game_img.image,
			&g->game_img.bpp, &g->game_img.line_length, &g->game_img.endian);
	mlx_hook(g->window_ptr, 17, 0L, exit_game, NULL);
	mlx_hook(g->window_ptr, 2, 1L << 0, key_press, NULL);
	mlx_hook(g->window_ptr, 3, 1L << 1, key_release, NULL);
	mlx_loop_hook(_map()->graphics->mlx_ptr, &update_window, NULL);
}

/* Open all four textures. */
void	open_all_textures(void)
{
	open_texture(&_map()->params->n_texture);
	open_texture(&_map()->params->e_texture);
	open_texture(&_map()->params->s_texture);
	open_texture(&_map()->params->w_texture);
}

/* Open a texture file, check it was correctly opened and that it is square.
 * Then assign its parameters in the image structure. */
void	open_texture(t_img *texture)
{
	int		texture_width;
	int		texture_height;

	texture->image = mlx_xpm_file_to_image(_map()->graphics->mlx_ptr,
			texture->path, &texture_width, &texture_height);
	if (!texture->image)
		ft_exit("texture file open failed", 1);
	if (texture_width != 64 || texture_width != texture_height)
		ft_exit("textures must be 64x64", 1);
	assign_texture_parameters(texture, texture_width);
}
