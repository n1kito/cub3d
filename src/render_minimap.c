/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:57 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:15:34 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Place tiles on minimap image. */
void	place_minimap_tiles(int pos[2], int lim[2], int minimap[2], char **map)
{
	t_params	*p;

	p = _map()->params;
	minimap[1] = 0;
	while (pos[1] < lim[1] && _map()->map[pos[1]])
	{
		pos[0] = lim[0] - 10;
		minimap[0] = 0;
		while (pos[0] < lim[0] && map[pos[1]][pos[0]])
		{
			coords_init(minimap[0] * MINI_TILE,
				minimap[1] * MINI_TILE, MINI_TILE, MINI_TILE);
			if (map[pos[1]][pos[0]] == '1')
				ft_put_rectangle(&_map()->graphics->minimap_img,
					p->c_color);
			else if (map[pos[1]][pos[0]] == '0'
					|| is_start_position(map[pos[1]][pos[0]]))
				ft_put_rectangle(&_map()->graphics->minimap_img,
					p->f_color);
			pos[0]++;
			minimap[0]++;
		}
		pos[1]++;
		minimap[1]++;
	}
}

/* Draws base map on minimap image. */
void	render_minimap(t_mlx *g, char **map)
{
	int	pos[2];
	int	lim[2];
	int	minimap[2];

	coords_init(0, 0, g->minimap_height, g->minimap_width);
	ft_put_rectangle(&g->minimap_img, BLACK);
	init_minimap_values(pos, lim);
	place_minimap_tiles(pos, lim, minimap, map);
	render_player_dot_on_minimap(lim);
}

/* Place player position dot on top of minimap image. */
void	render_player_dot_on_minimap(int *draw_end)
{
	double		dot_pos[2];
	t_img		minimap_img;
	t_params	*p;

	p = _map()->params;
	minimap_img = _map()->graphics->minimap_img;
	dot_pos[0] = (_map()->plyr.x * SCALE_FACTOR)
		- (draw_end[0] - 10) * MINI_TILE;
	dot_pos[1] = (_map()->plyr.y * SCALE_FACTOR)
		- (draw_end[1] - 10) * MINI_TILE;
	coords_init(dot_pos[0], dot_pos[1],
		dot_pos[0] + cos(_map()->plyr.rot_angle) * 10,
		dot_pos[1] + sin(_map()->plyr.rot_angle) * 10);
	ft_draw_line(&minimap_img, p->c_color);
	ft_put_circle(&minimap_img, dot_pos, MINI_TILE * 0.5 / 3, p->c_color);
	_map()->graphics->minimap_dot_pos[0] = dot_pos[0];
	_map()->graphics->minimap_dot_pos[1] = dot_pos[1];
}

void	init_minimap_values(int draw_pos[2], int draw_end[2])
{
	draw_pos[0] = 0;
	draw_pos[1] = 0;
	if ((_map()->plyr.x * SCALE_FACTOR) / MINI_TILE >= 5)
		draw_pos[0] = ((_map()->plyr.x * SCALE_FACTOR) / MINI_TILE) - 5;
	if ((_map()->plyr.y * SCALE_FACTOR) / MINI_TILE >= 5)
		draw_pos[1] = ((_map()->plyr.y * SCALE_FACTOR) / MINI_TILE) - 5;
	draw_end[0] = draw_pos[0] + 10;
	draw_end[1] = draw_pos[1] + 10;
}
