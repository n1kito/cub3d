#include "cub3D.h"

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
			coords_init(minimap[0] * g->minimap_tile,
						minimap[1] * g->minimap_tile, g->minimap_tile, g->minimap_tile);
			if (map[pos[1]][pos[0]] == '0' || is_start_position(map[pos[1]][pos[0]]))
				ft_put_rectangle(&g->minimap_img, SOL_1);
			else if (map[pos[1]][pos[0]] == '1')
				ft_put_rectangle(&g->minimap_img, XMUR_1);
			pos[0]++;
			minimap[0]++;
		}
		pos[1]++;
		minimap[1]++;
	}
	render_player_dot_on_minimap(lim);
} 

void	render_player_dot_on_minimap(int *draw_end)
{
	double	dot_pos[2];
	int		tile_size;
	t_img	minimap_img;

	_map()->graphics->minimap_draw_end[0] = draw_end[0];
	_map()->graphics->minimap_draw_end[1] = draw_end[1];
	tile_size = _map()->graphics->minimap_tile;
	minimap_img = _map()->graphics->minimap_img;
	dot_pos[0] = (_map()->plyr.x * SCALE_FACTOR) - (draw_end[0] - 10) * tile_size; // TODO fix this
	dot_pos[1] = (_map()->plyr.y * SCALE_FACTOR) - (draw_end[1] - 10) * tile_size; // TODO fix this
	if (_map()->plyr.x > _map()->map_width * TILE_SIZE)
		ft_exit("player left map", 1);
	// printf("draw_pos(%f, %f)\n", dot_pos[0], dot_pos[1]);
	ft_put_circle(&minimap_img, dot_pos[0], dot_pos[1], tile_size * 0.5 / 5, RED);
	coords_init(dot_pos[0], dot_pos[1], dot_pos[0] + cos(_map()->plyr.rot_angle) * 20, dot_pos[1] + sin(_map()->plyr.rot_angle) * 20);
	ft_draw_line(&minimap_img, RED);
	_map()->graphics->minimap_dot_pos[0] = dot_pos[0];
	_map()->graphics->minimap_dot_pos[1] = dot_pos[1];
}

void	init_minimap_values(int draw_pos[2], int draw_end[2])
{
	draw_pos[0] = 0;
	draw_pos[1] = 0;
	if ((_map()->plyr.x * SCALE_FACTOR) / _map()->graphics->minimap_tile >= 5)
		draw_pos[0] = ((_map()->plyr.x * SCALE_FACTOR) / _map()->graphics->minimap_tile) - 5;
	if ((_map()->plyr.y  * SCALE_FACTOR) / _map()->graphics->minimap_tile >= 5)
		draw_pos[1] = ((_map()->plyr.y * SCALE_FACTOR) / _map()->graphics->minimap_tile) - 5;
	// printf("plyr_pos(%f, %f)\n", _map()->plyr.x, _map()->plyr.y);
	draw_end[0] = draw_pos[0] + 10;
	draw_end[1] = draw_pos[1] + 10;
}

// pl  160 224
// dot 319 447