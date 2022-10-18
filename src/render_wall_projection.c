//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

/* Draws each projection line on game image. */
void	generate_projection(void)
{
	int				i;
	t_projection	p;

	i = 0;
	while (i < NUM_RAYS)
	{
		init_projection_values(&p, i);
		// draw sky
		coords_init(i, 0, p.wall_top_pixel, 1);
		ft_put_rectangle_gradient(&_map()->graphics->game_img, PLA_1);
		// draw wall
		coords_init(i, p.wall_top_pixel, i, p.wall_bottom_pixel);
		// calculate texture_offset_x
		t_img *texture;
		if (_map()->rays[i].was_hit_vertical && _map()->rays[i].is_ray_facing_right)
			texture = &_map()->params->e_texture;
		else if (_map()->rays[i].was_hit_vertical && _map()->rays[i].is_ray_facing_left)
			texture = &_map()->params->w_texture;
		else if (!_map()->rays[i].was_hit_vertical && _map()->rays[i].is_ray_facing_up)
			texture = &_map()->params->n_texture;
		else if (!_map()->rays[i].was_hit_vertical && _map()->rays[i].is_ray_facing_down)
				texture = &_map()->params->s_texture;
		int texture_offset_x, texture_offset_y;
		if (_map()->rays[i].was_hit_vertical)
		{
			texture_offset_x = (int)_map()->rays[i].wall_hit_y % texture->sprite_size;
		}
		else
		{
			texture_offset_x = (int)_map()->rays[i].wall_hit_x % texture->sprite_size;
		}
		for (int y = p.wall_top_pixel; y < p.wall_bottom_pixel; y++)
		{
			int	distance_from_top = y + (p.wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
			// TODO calculate texture_offset_y
			texture_offset_y = distance_from_top * ((float)texture->sprite_size / p.wall_strip_height);
			char *texel_color = texture->addr + (texture_offset_y * texture->line_length + texture_offset_x * (texture->bpp / 8));
			// if (_map()->rays[i].was_hit_vertical)
			// 	ft_draw_line(&_map()->graphics->game_img, XMUR_1);
			// else
			// 	ft_draw_line(&_map()->graphics->game_img, YMUR_1);
			ft_pixel_put(&_map()->graphics->game_img, i, y, *(int *)texel_color);
		}
		// draw floor
		coords_init(i, p.wall_bottom_pixel,
			WINDOW_HEIGHT - p.wall_top_pixel, 1);
		ft_put_rectangle_gradient(&_map()->graphics->game_img, SOL_1);
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
	// if (p->wall_strip_height > WINDOW_HEIGHT)
	// 	p->wall_strip_height = WINDOW_HEIGHT;
	p->wall_top_pixel = (WINDOW_HEIGHT / 2) - (p->wall_strip_height / 2);
	if (p->wall_top_pixel < 0)
		p->wall_top_pixel = 0;
	p->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (p->wall_strip_height / 2);
	if (p->wall_bottom_pixel > WINDOW_HEIGHT)
		p->wall_bottom_pixel = WINDOW_HEIGHT;
}
