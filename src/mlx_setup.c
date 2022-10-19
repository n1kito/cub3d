//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

void	mlx_setup(void)
{
	t_map	*m;
	t_mlx	*g;

	m = _map();
	g = m->graphics;
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		ft_exit("mlx_init() fail [mlx_setup()]", 1);
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

int	update_window(void)
{
	t_mlx	*g;

	g = _map()->graphics;
	move_player();
	cast_all_rays();
	generate_projection();
	mlx_put_image_to_window(g->mlx_ptr, g->window_ptr, g->game_img.image, 0, 0);
	mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 20, WHITE, "(m) minimap");
	mlx_string_put(g->mlx_ptr, g->window_ptr, 15, 35, WHITE, "(q) quit");
	if (_map()->is_minimap_open)
	{
		render_minimap(_map()->graphics, _map()->map);
		// render_rays();
		mlx_clear_window(g->mlx_ptr, g->minimap_window_ptr);
		mlx_put_image_to_window(g->mlx_ptr, g->minimap_window_ptr,
			g->minimap_img.image,
			(g->minimap_width - 3 * MINI_TILE) / 2 - g->minimap_dot_pos[0],
			(g->minimap_height - 3 * MINI_TILE) / 2 - g->minimap_dot_pos[1]);
	}
	return (0);
}

void	init_hooks(void)
{
	t_mlx		*g;
	t_params	*p;

	g = _map()->graphics;
	p = _map()->params;
	_map()->plyr.x = p->pl_start_pos[0] * TILE_SIZE + TILE_SIZE / 2;
	_map()->plyr.y = p->pl_start_pos[1] * TILE_SIZE + TILE_SIZE / 2;
	g->minimap_img.image = mlx_new_image(g->mlx_ptr,
			g->minimap_width, g->minimap_height);
	g->game_img.image = mlx_new_image(g->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->minimap_img.image || !g->game_img.image)
		ft_exit("mlx_new_image() failed [init_hooks()]", 1);
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
