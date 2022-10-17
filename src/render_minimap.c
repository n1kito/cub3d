#include "cub3D.h"

/* Draws base map on minimap image. */
void	render_minimap(t_mlx *g, char **map)
{
	int	pos[2];
	int	lim[2];
	int	minimap[2];

	coords_init(0, 0, g->minimap_height, g->minimap_width);
	ft_put_rectangle(&g->minimap_img, BLACK);
	// reset minimap image
//	mlx_destroy_image(&g->mlx_ptr, &g->minimap_img.image);
//	g->minimap_img.image = mlx_new_image(g->mlx_ptr, g->minimap_width, g->minimap_height);
	// todo: check failure
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
			if (map[pos[1]][pos[0]] == '1')
				ft_put_rectangle(&g->minimap_img, XMUR_1);
			else if (map[pos[1]][pos[0]] == '0' || map[pos[1]][pos[0]] == 'N') // TODO add other starting positions
				ft_put_rectangle(&g->minimap_img, SOL_1);
			pos[0]++;
			minimap[0]++;
		}
		pos[1]++;
		minimap[1]++;
	}
	render_player_dot_on_minimap(lim);
} 

/* Place player dot on top of minimap image. */
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
	// coords_init(dot_pos[0], dot_pos[1], dot_pos[0] + cos(_map()->plyr.rot_angle) * 10, dot_pos[1] + sin(_map()->plyr.rot_angle) * 10);
	// ft_draw_line(&minimap_img, TEAL);
	ft_put_circle(&minimap_img, dot_pos[0], dot_pos[1], tile_size * 0.5 / 3, TEAL);
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
	draw_end[0] = draw_pos[0] + 10;
	draw_end[1] = draw_pos[1] + 10;
}

void	render_rays(void)
{
	int		i;
	double	ray_coords[4];

	i = 0;
	while (i < NUM_RAYS)
	{
		// coords_init(SCALE_FACTOR * _map()->plyr.x,
		// 			SCALE_FACTOR * _map()->plyr.y,
		// 			SCALE_FACTOR * _map()->rays[i].wall_hit_x,
		// 			SCALE_FACTOR * _map()->rays[i].wall_hit_y);
		ray_coords[0] = (_map()->plyr.x * SCALE_FACTOR)
						- (_map()->graphics->minimap_draw_end[0] - 10) * MINI_TILE;
		ray_coords[1] = (_map()->plyr.y * SCALE_FACTOR)
						- (_map()->graphics->minimap_draw_end[1] - 10) * MINI_TILE;
		ray_coords[2] = (_map()->rays[i].wall_hit_x * SCALE_FACTOR)
						- (_map()->graphics->minimap_draw_end[0] - 10) * MINI_TILE;
		// TODO check that the following works, added to keep the rays from reapearing on the wrong side of the window
		if (ray_coords[2] > _map()->graphics->minimap_width)
			ray_coords[2] = _map()->graphics->minimap_width;
		else if (ray_coords[2] < 0)
			ray_coords[2] = 0;
		// check ends here
		ray_coords[3] = (_map()->rays[i].wall_hit_y * SCALE_FACTOR)
						- (_map()->graphics->minimap_draw_end[1] - 10) * MINI_TILE;
		// TODO check that the following works, added to keep the rays from reapearing on the wrong side of the window
		if (ray_coords[3] > _map()->graphics->minimap_height)
			ray_coords[3] = _map()->graphics->minimap_height;
		else if (ray_coords[3] < 0)
			ray_coords[3] = 0;
		// check ends here
		coords_init(ray_coords[0], ray_coords[1], ray_coords[2], ray_coords[3]);
		ft_draw_line(&_map()->graphics->minimap_img, TEAL);
		i++;
	}
}
