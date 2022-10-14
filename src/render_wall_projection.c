#include "cub3D.h"

/* Draws each projection line on game image. */
void	generate_projection(void)
{
	int				i;
	t_projection	p;

	i = 0;
	while (i < NUM_RAYS)
	{
		init_projection_values(&p, i);
		coords_init(i, 0, p.wall_top_pixel, 1);
		ft_put_rectangle_deg(&_map()->graphics->game_img, PLA_1);
		coords_init(i, p.wall_top_pixel, i, p.wall_bottom_pixel);
		if (_map()->rays[i].was_hit_vertical)
			ft_draw_line(&_map()->graphics->game_img, XMUR_1);
		else
			ft_draw_line(&_map()->graphics->game_img, YMUR_1);
		coords_init(i, p.wall_bottom_pixel,
			WINDOW_HEIGHT - p.wall_top_pixel, 1);
		ft_put_rectangle_deg(&_map()->graphics->game_img, SOL_1);
		i++;
	}
}

/* Calculates values necessary to draw each frame. */
void	init_projection_values(t_projection *p, int i)
{
	p->perp_distance = _map()->rays[i].distance
		* cos(_map()->rays[i].ray_angle - _map()->plyr.rot_angle);
	p->distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	p->projected_wall_height = (TILE_SIZE / p->perp_distance)
		* p->distance_proj_plane;
	p->wall_strip_height = (int)p->projected_wall_height;
	if (p->wall_strip_height > WINDOW_HEIGHT)
		p->wall_strip_height = WINDOW_HEIGHT;
	p->wall_top_pixel = (WINDOW_HEIGHT / 2) - (p->wall_strip_height / 2);
	if (p->wall_top_pixel < 0)
		p->wall_top_pixel = 0;
	p->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (p->wall_strip_height / 2);
	if (p->wall_bottom_pixel < 0)
		p->wall_bottom_pixel = 0;
}
