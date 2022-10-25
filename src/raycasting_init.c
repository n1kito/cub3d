/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:04 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:15:17 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Sets values necessary to identify horizontal interceptions. */
void	init_horz_intercepts(t_raycasting *r)
{
	r->y_intercept = floor(_map()->plyr.y / TILE_SIZE) * TILE_SIZE;
	if (r->ray_is_facing_down)
		r->y_intercept += TILE_SIZE;
	r->x_intercept = _map()->plyr.x
		+ (r->y_intercept - _map()->plyr.y) / tan(r->ray_angle);
	r->y_step = TILE_SIZE;
	if (r->ray_is_facing_up)
		r->y_step *= -1;
	r->x_step = TILE_SIZE / tan(r->ray_angle);
	if (r->ray_is_facing_left && r->x_step > 0)
		r->x_step *= -1;
	if (r->ray_is_facing_right && r->x_step < 0)
		r->x_step *= -1;
}

/* Sets values necessary to identify vertical interceptions. */
void	init_vert_intercepts(t_raycasting *r)
{
	r->x_intercept = floor(_map()->plyr.x / TILE_SIZE) * TILE_SIZE;
	if (r->ray_is_facing_right)
		r->x_intercept += TILE_SIZE;
	r->y_intercept = _map()->plyr.y
		+ (r->x_intercept - _map()->plyr.x) * tan(r->ray_angle);
	r->x_step = TILE_SIZE;
	if (r->ray_is_facing_left)
		r->x_step *= -1;
	r->y_step = TILE_SIZE * tan(r->ray_angle);
	if (r->ray_is_facing_up && r->y_step > 0)
		r->y_step *= -1;
	if (r->ray_is_facing_down && r->y_step < 0)
		r->y_step *= -1;
}

/* Sets values required by the raycasting process. */
void	init_raycasting_values(t_raycasting *r, float ray_angle)
{
	r->ray_angle = normalize_angle(ray_angle);
	r->ray_is_facing_down = (r->ray_angle > 0 && r->ray_angle < PI);
	r->ray_is_facing_up = !r->ray_is_facing_down;
	r->ray_is_facing_right = ((r->ray_angle < (0.5 * PI))
			|| (r->ray_angle > (1.5 * PI)));
	r->ray_is_facing_left = !r->ray_is_facing_right;
	r->found_horz_wall_hit = FALSE;
	r->horz_wall_hit_x = 0;
	r->horz_wall_hit_y = 0;
	r->found_vert_wall_hit = FALSE;
	r->vert_wall_hit_x = 0;
	r->vert_wall_hit_y = 0;
}
