#include "cub3D.h"

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
		g->window_width, g->window_height,
		m->map_name);
	g->minimap_window_ptr = mlx_new_window(g->mlx_ptr,
			g->minimap_width - 2 * MINI_TILE,
			g->minimap_height - 2 * MINI_TILE,
			"MINIMAP");
	if (!g->window_ptr || !g->minimap_window_ptr)
		ft_exit("failed to create window [mlx_setup()]", 1);
	// minimap image has to be bigger than its window
	g->minimap_img.image = mlx_new_image(g->mlx_ptr, g->minimap_width, g->minimap_height);
	g->game_img.image = mlx_new_image(g->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->game_img.image || !g->minimap_img.image)
		ft_exit("failed to create images", 1);
}

int	key_press(int key, void *param)
{
	(void)param;
	if (key == UP)
		_map()->plyr.move = 1;
	else if (key == DOWN)
		_map()->plyr.move = -1;
	else if (key == LEFT)
		_map()->plyr.move = 2;
	else if (key == RIGHT)
		_map()->plyr.move = -2;
	else if (key == ARROW_LEFT)
		_map()->plyr.rot = -1;
	else if (key == ARROW_RIGHT)
		_map()->plyr.rot = 1;
	else if (key == ESC)
		exit_game();
	// update_POV();
	// update_minimap();
	return (0);
}

int key_release(int key, void *param)
{
	(void)param;
	if (key == UP)
		_map()->plyr.move = 0;
	else if (key == DOWN)
		_map()->plyr.move = 0;
	if (key == LEFT)
		_map()->plyr.move = 0;
	if (key == RIGHT)
		_map()->plyr.move = 0;
	else if (key == ARROW_LEFT)
		_map()->plyr.rot = 0;
	else if (key == ARROW_RIGHT)
		_map()->plyr.rot = 0;
	return (0);
}

void	move_player(void)
{
	float	new_x;
	float	new_y;
	double	tmp_rot;

	_map()->plyr.rot_angle += _map()->plyr.rot * 0.09;
	if (_map()->plyr.move == 2)
	{
		tmp_rot = (_map()->plyr.rot_angle + 80.12);
		new_x = (_map()->plyr.x + cos(tmp_rot) * 5);
		new_y = (_map()->plyr.y + sin(tmp_rot) * 5);
	}
	else if (_map()->plyr.move == -2)
	{
		tmp_rot = (_map()->plyr.rot_angle + 80.12);
		new_x = (_map()->plyr.x + -cos(tmp_rot) * 5);
		new_y = (_map()->plyr.y + -sin(tmp_rot) * 5);
	}
	else
	{
		new_x = (_map()->plyr.x + (cos(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
		new_y = (_map()->plyr.y + (sin(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
	}
	if (!map_has_wall_at(new_x, _map()->plyr.y))
		_map()->plyr.x = new_x;
	if (!map_has_wall_at(_map()->plyr.x, new_y))
		_map()->plyr.y = new_y;
}

int update_window(void)
{
	move_player();
	cast_all_rays();
	render_minimap(_map()->graphics, _map()->map);
	render_rays();
	generate_projection();
	mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->game_img.image, 0, 0);
	mlx_clear_window(_map()->graphics->mlx_ptr, _map()->graphics->minimap_window_ptr);
	// image should be put to window so dot is always in the center of the minimap window
	mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->minimap_window_ptr, _map()->graphics->minimap_img.image, (_map()->graphics->minimap_width - 2 * MINI_TILE) / 2 - _map()->graphics->minimap_dot_pos[0], (_map()->graphics->minimap_height - 2 * MINI_TILE) / 2 - _map()->graphics->minimap_dot_pos[1]);
	return (0);
}

void	init_hooks(void)
{

	// Initialise player position to center of start position square
	_map()->plyr.x = _map()->params->pl_start_pos[0] * TILE_SIZE + TILE_SIZE / 2;
	_map()->plyr.y = _map()->params->pl_start_pos[1] * TILE_SIZE + TILE_SIZE / 2;
	_map()->graphics->minimap_img.image = mlx_new_image(_map()->graphics->mlx_ptr, _map()->graphics->minimap_width, _map()->graphics->minimap_height);
	_map()->graphics->game_img.image = mlx_new_image(_map()->graphics->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// TODO protect
	// TODO move minimap rendering
	_map()->graphics->minimap_img.addr = mlx_get_data_addr(_map()->graphics->minimap_img.image, &_map()->graphics->minimap_img.bpp, &_map()->graphics->minimap_img.line_length, &_map()->graphics->minimap_img.endian);
	_map()->graphics->game_img.addr = mlx_get_data_addr(_map()->graphics->game_img.image, &_map()->graphics->game_img.bpp, &_map()->graphics->game_img.line_length, &_map()->graphics->game_img.endian);
	// render_minimap(_map()->graphics, _map()->map);
	// render_player_position();
	// mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
	// exit when pressing X
	mlx_hook(_map()->graphics->window_ptr, 17, 0L, exit_game, NULL);
	// mlx_key_hook(_map()->graphics->window_ptr, &move_player, NULL);
	mlx_hook(_map()->graphics->window_ptr, 2, 1L << 0, key_press, NULL);
	mlx_hook(_map()->graphics->window_ptr, 3, 1L << 1, key_release, NULL);
	// update_window();
	mlx_loop_hook(_map()->graphics->mlx_ptr, &update_window, NULL);
}
