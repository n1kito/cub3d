/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:54 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:15:36 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		draw_sky(p, i);
		draw_walls(p, i);
		draw_floor(p, i);
		i++;
	}
}

/* Calculates values necessary to draw each 'ray' column. */
void	init_projection_values(t_projection *p, int i)
{
	p->perp_distance = _map()->rays[i].distance
		* cos(_map()->rays[i].ray_angle - _map()->plyr.rot_angle);
	p->projected_wall_height = (TILE_SIZE / p->perp_distance)
		* _map()->dist_proj_plane;
	p->wall_strip_height = (int)p->projected_wall_height;
	p->wall_top_pixel = (WINDOW_HEIGHT / 2) - (p->wall_strip_height / 2);
	if (p->wall_top_pixel < 0)
		p->wall_top_pixel = 0;
	p->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (p->wall_strip_height / 2);
	if (p->wall_bottom_pixel > WINDOW_HEIGHT)
		p->wall_bottom_pixel = WINDOW_HEIGHT;
}
