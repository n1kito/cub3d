/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_move_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:11 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 13:39:30 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* If minimap is not open, window is opened and hooks are setup.
 * Else, the window is destroyed (but not the minimap image), */
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

/* Toggles fast/slow move and rotation speeds. */
void	toggle_mode_dell(void)
{
	if (_map()->plyr.mode_dell == 0)
	{
		_map()->plyr.mv_speed = 3;
		_map()->plyr.rot_speed = 0.031;
		_map()->plyr.mode_dell = 1;
	}
	else
	{
		_map()->plyr.mv_speed = 5;
		_map()->plyr.rot_speed = 0.09;
		_map()->plyr.mode_dell = 0;
	}
}

/* Sets the actions corresponding to each key press. */
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
	else if (key == KEY_F)
		toggle_mode_dell();
	return (0);
}

/* Sets the actions corresponding to each key release. */
int	key_release(int key, void *param)
{
	(void)param;
	if (key == UP || key == DOWN)
		_map()->plyr.move = 0;
	else if (key == LEFT || key == RIGHT)
		_map()->plyr.side = 0;
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		_map()->plyr.rot = 0;
	return (0);
}

/* Updates player position coordinates depending on its walk direction
 * and rotation angle. */
void	move_player(t_player *p)
{
	float		new[2];

	p->rot_angle += p->rot * p->rot_speed;
	if (p->side == -1 && p->move == 0)
		update_pos(new, p->x + cos(p->rot_angle + (PI / 2)) * p->mv_speed,
			p->y + sin(p->rot_angle + (PI / 2)) * p->mv_speed);
	else if (p->side == 1 && p->move == 0)
		update_pos(new, p->x + -cos(p->rot_angle + (PI / 2)) * p->mv_speed,
			p->y + -sin(p->rot_angle + (PI / 2)) * p->mv_speed);
	else if (p->side == 1 && p->move == 1)
		update_pos(new, p->x + cos(p->rot_angle + 81) * p->mv_speed,
			p->y + sin(p->rot_angle + 81) * p->mv_speed);
	else if (p->side == -1 && p->move == 1)
		update_pos(new, p->x + cos(p->rot_angle + 82.4) * p->mv_speed,
			p->y + sin(p->rot_angle + 82.4) * p->mv_speed);
	else
		update_pos(new, p->x + (cos(p->rot_angle) * p->move) * p->mv_speed,
			p->y + (sin(p->rot_angle) * p->move) * p->mv_speed);
	if (!wall_at(new[0] + 1, p->y + 1) && !wall_at(new[0] - 1, p->y - 1)
		&& !wall_at(new[0], p->y))
		p->x = new[0];
	if (!wall_at(p->x + 1, new[1] + 1) && !wall_at(p->x - 1, new[1] - 1)
		&& !wall_at(p->x, new[1]))
		p->y = new[1];
}
