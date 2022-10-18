//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Draws base map on minimap image. */
void	render_minimap(t_mlx *g, char **map)
{
	int	pos[2];
	int	lim[2];
	int	minimap[2];

	coords_init(0, 0, g->minimap_height, g->minimap_width);
	ft_put_rectangle(&g->minimap_img, BLACK);
	init_minimap_values(pos, lim);
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
				ft_put_rectangle(&g->minimap_img, XMUR_1);
			else if (map[pos[1]][pos[0]] == '0'
				|| is_start_position(map[pos[1]][pos[0]]))
				ft_put_rectangle(&g->minimap_img, SOL_1);
			pos[0]++;
			minimap[0]++;
		}
		pos[1]++;
		minimap[1]++;
	}
	render_player_dot_on_minimap(lim);
}

//void	draw_arrow(double dot_pos[2])
//{
//	double	arrow_width = _map()->graphics->minimap_tile * 0.5 / 3;
//	double	arrow_len = 1.2;
//	double	line_coord[4];
//	double	angle;
//
//	angle = _map()->plyr.rot_angle - 0.5 * PI;
//	line_coord[0] = dot_pos[0];
//	line_coord[1] = dot_pos[1];
//	line_coord[2] = dot_pos[0];
//	line_coord[3] = dot_pos[1];
//	double i = 0;
//	double j = 0;
//	while (i < arrow_len)
//	{
//		if (j > arrow_width)
//			j = arrow_width;
//		line_coord[0] = line_coord[0] + (j * cos(angle));
//		line_coord[1] = line_coord[1] + (j * sin(angle));
//		line_coord[2] = line_coord[2] + (i * cos(_map()->plyr.rot_angle));
//		line_coord[3] = line_coord[3] + (i * sin(_map()->plyr.rot_angle));
//		coords_init(line_coord[0], line_coord[1], line_coord[2], line_coord[3]);
//		ft_draw_line(&_map()->graphics->minimap_img, TEAL);
//		i += 0.1;
//		j += 0.1;
//	}
//}

/* Place player dot on top of minimap image. */
void	render_player_dot_on_minimap(int *draw_end)
{
	double	dot_pos[2];
	t_img	minimap_img;

	_map()->graphics->minimap_draw_end[0] = draw_end[0];
	_map()->graphics->minimap_draw_end[1] = draw_end[1];
	minimap_img = _map()->graphics->minimap_img;
	dot_pos[0] = (_map()->plyr.x * SCALE_FACTOR) - (draw_end[0] - 10) * MINI_TILE;
	dot_pos[1] = (_map()->plyr.y * SCALE_FACTOR) - (draw_end[1] - 10) * MINI_TILE;
	coords_init(dot_pos[0], dot_pos[1], dot_pos[0] + cos(_map()->plyr.rot_angle) * 10, dot_pos[1] + sin(_map()->plyr.rot_angle) * 10);
	ft_draw_line(&minimap_img, TEAL);
	ft_put_circle(&minimap_img, dot_pos, MINI_TILE * 0.5 / 3, TEAL);
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
