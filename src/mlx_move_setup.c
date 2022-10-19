//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

void	trigger_minimap(void)
{
	t_mlx	*g;

	g = _map()->graphics;
	if (!_map()->is_minimap_open)
	{
		g->minimap_window_ptr = mlx_new_window(g->mlx_ptr,
				g->minimap_width - 3 * MINI_TILE,
				g->minimap_height - 3 * MINI_TILE,
				"MINIMAP");
		mlx_hook(g->minimap_window_ptr, 17, 0L, exit_game, NULL);
		mlx_hook(g->minimap_window_ptr, 2, 1L << 0, key_press, NULL);
		mlx_hook(g->minimap_window_ptr, 3, 1L << 1, key_release, NULL);
		_map()->is_minimap_open = 1;
	}
	else
	{
		mlx_destroy_window(g->mlx_ptr, g->minimap_window_ptr);
		g->minimap_window_ptr = NULL;
		_map()->is_minimap_open = 0;
	}
}

int	key_press(int key, void *param)
{
	(void)param;
	if (key == UP)
		_map()->plyr.move = 1;
	else if (key == DOWN)
		_map()->plyr.move = -1;
	else if (key == LEFT)
		_map()->plyr.side = 1;
	else if (key == RIGHT)
		_map()->plyr.side = -1;
	else if (key == ARROW_LEFT)
		_map()->plyr.rot = -1;
	else if (key == ARROW_RIGHT)
		_map()->plyr.rot = 1;
	else if (key == ESC || key == KEY_Q)
		exit_game();
	else if (key == KEY_M)
		trigger_minimap();
	return (0);
}

int	key_release(int key, void *param)
{
	(void)param;
	if (key == UP || key == DOWN)
		_map()->plyr.move = 0;
	else if  (key == LEFT || key == RIGHT)
		_map()->plyr.side = 0;
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		_map()->plyr.rot = 0;
	return (0);
}

void	move_player(void)
{
	float		new_pos[2];
	t_player	*p;

	p = &_map()->plyr;
	p->rot_angle += p->rot * 0.09;

	if (_map()->plyr.side == 1 && _map()->plyr.move == 0)
	{
		new_pos[0] = (_map()->plyr.x + cos(_map()->plyr.rot_angle + 80.12) * 5);
		new_pos[1] = (_map()->plyr.y + sin(_map()->plyr.rot_angle + 80.12) * 5);
	}
	else if (_map()->plyr.side == -1 && _map()->plyr.move == 0)
	{
		new_pos[0] = (_map()->plyr.x + -cos(_map()->plyr.rot_angle + 80.12) * 5);
		new_pos[1] = (_map()->plyr.y + -sin(_map()->plyr.rot_angle + 80.12) * 5);
	}
	else if (_map()->plyr.side == 1 && _map()->plyr.move == 1)
	{
		new_pos[0] = (_map()->plyr.x + cos(_map()->plyr.rot_angle + 81) * 5);
		new_pos[1] = (_map()->plyr.y + sin(_map()->plyr.rot_angle + 81) * 5);
	}
	else if (_map()->plyr.side == -1 && _map()->plyr.move == 1)
	{
		new_pos[0] = (_map()->plyr.x + cos(_map()->plyr.rot_angle + 82.4) * 5);
		new_pos[1] = (_map()->plyr.y + sin(_map()->plyr.rot_angle + 82.4) * 5);
	}
	else
	{
		new_pos[0] = (_map()->plyr.x + (cos(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
		new_pos[1] = (_map()->plyr.y + (sin(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
	}

	// if (p->move == 2)
	// {
	// 	new_pos[0] = (p->x + cos(p->rot_angle + 80.12) * 5);
	// 	new_pos[1] = (p->y + sin(p->rot_angle + 80.12) * 5);
	// }
	// else if (p->move == -2)
	// {
	// 	new_pos[0] = (p->x + -cos(p->rot_angle + 80.12) * 5);
	// 	new_pos[1] = (p->y + -sin(p->rot_angle + 80.12) * 5);
	// }
	// else
	// {
	// 	new_pos[0] = (p->x + (cos(p->rot_angle) * p->move) * 5);
	// 	new_pos[1] = (p->y + (sin(p->rot_angle) * p->move) * 5);
	// }
	if (!map_has_wall_at(new_pos[0], p->y))
		p->x = new_pos[0];
	if (!map_has_wall_at(p->x, new_pos[1]))
		p->y = new_pos[1];
}
