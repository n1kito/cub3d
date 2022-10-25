/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:59 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:15:31 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Returns correct texture pointer depending on wall and ray orientations. */
t_img	*pick_texture(int i)
{
	if (_map()->rays[i].was_hit_vertical
		&& _map()->rays[i].is_ray_facing_right)
		return (&_map()->params->e_texture);
	else if (_map()->rays[i].was_hit_vertical
		&& _map()->rays[i].is_ray_facing_left)
		return (&_map()->params->w_texture);
	else if (!_map()->rays[i].was_hit_vertical
		&& _map()->rays[i].is_ray_facing_up)
		return (&_map()->params->n_texture);
	else if (!_map()->rays[i].was_hit_vertical
		&& _map()->rays[i].is_ray_facing_down)
		return (&_map()->params->s_texture);
	return (NULL);
}

/* Draws sky for pixel column of index i. */
void	draw_sky(t_projection p, int i)
{
	int	ceiling_color;

	ceiling_color = _map()->params->c_color;
	coords_init(i, 0, p.wall_top_pixel, 1);
	ft_put_rectangle(&_map()->graphics->game_img, ceiling_color);
}

/* Draws wall textures for pixel column of index i. */
void	draw_walls(t_projection p, int i)
{
	int		y;
	int		texture_offset[2];
	int		distance_from_top;
	char	*texel_color;
	t_img	*texture;

	texture = pick_texture(i);
	if (_map()->rays[i].was_hit_vertical)
		texture_offset[0] = ((int)_map()->rays[i].wall_hit_y
				% texture->sprite_size);
	else
		texture_offset[0] = ((int)_map()->rays[i].wall_hit_x
				% texture->sprite_size);
	y = p.wall_top_pixel;
	while (y < p.wall_bottom_pixel)
	{
		distance_from_top = y + (p.wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
		texture_offset[1] = distance_from_top
			* ((float)texture->sprite_size / p.wall_strip_height);
		texel_color = texture->addr + (texture_offset[1] * texture->line_length
				+ texture_offset[0] * (texture->bpp / 8));
		ft_pixel_put(&_map()->graphics->game_img, i, y, *(int *)texel_color);
		y++;
	}
}

/* Draws floor for pixel column of index i. */
void	draw_floor(t_projection p, int i)
{
	int	floor_color;

	floor_color = _map()->params->f_color;
	coords_init(i, p.wall_bottom_pixel,
		WINDOW_HEIGHT - p.wall_top_pixel, 1);
	ft_put_rectangle(&_map()->graphics->game_img, floor_color);
}
