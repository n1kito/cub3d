/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:00 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 11:04:49 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Calculates distance to wall intersection. */
void	calculate_wall_hit_distances(t_raycasting *r)
{
	if (r->found_horz_wall_hit)
		r->horz_hit_distance = distance_between_points(_map()->plyr.x,
				_map()->plyr.y, r->horz_wall_hit_x, r->horz_wall_hit_y);
	else
		r->horz_hit_distance = (float)INT_MAX;
	if (r->found_vert_wall_hit)
		r->vert_hit_distance = distance_between_points(_map()->plyr.x,
				_map()->plyr.y, r->vert_wall_hit_x, r->vert_wall_hit_y);
	else
		r->vert_hit_distance = (float)INT_MAX;
}

/* Finds first horizontal grid intersection. */
void	find_horz_grid_intersection(t_raycasting *r)
{
	init_horz_intercepts(r);
	r->next_horz_touch_x = r->x_intercept;
	r->next_horz_touch_y = r->y_intercept;
	while (r->next_horz_touch_x >= 0 && r->next_horz_touch_y >= 0)
	{
		r->x_to_check = r->next_horz_touch_x;
		r->y_to_check = r->next_horz_touch_y;
		if (r->ray_is_facing_up)
			r->y_to_check -= 1;
		else
			r->y_to_check = r->next_horz_touch_y;
		if (wall_at(r->x_to_check, r->y_to_check))
		{
			r->horz_wall_hit_x = r->next_horz_touch_x;
			r->horz_wall_hit_y = r->next_horz_touch_y;
			r->found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			r->next_horz_touch_x += r->x_step;
			r->next_horz_touch_y += r->y_step;
		}
	}
}

/* Finds first vertical grid intersection. */
void	find_vert_grid_intersection(t_raycasting *r)
{
	init_vert_intercepts(r);
	r->next_vert_touch_x = r->x_intercept;
	r->next_vert_touch_y = r->y_intercept;
	while (r->next_vert_touch_x >= 0 && r->next_vert_touch_y >= 0)
	{
		r->x_to_check = r->next_vert_touch_x;
		if (r->ray_is_facing_left)
			r->x_to_check -= 1;
		r->y_to_check = r->next_vert_touch_y;
		if (wall_at(r->x_to_check, r->y_to_check))
		{
			r->vert_wall_hit_x = r->next_vert_touch_x;
			r->vert_wall_hit_y = r->next_vert_touch_y;
			r->found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			r->next_vert_touch_x += r->x_step;
			r->next_vert_touch_y += r->y_step;
		}
	}
}

/* Casts a ray from player position depending on player rotation. */
void	cast_ray(float ray_angle, int column)
{
	t_raycasting	r;

	init_raycasting_values(&r, ray_angle);
	find_horz_grid_intersection(&r);
	find_vert_grid_intersection(&r);
	calculate_wall_hit_distances(&r);
	if (r.vert_hit_distance < r.horz_hit_distance)
	{
		_map()->rays[column].distance = r.vert_hit_distance;
		_map()->rays[column].wall_hit_x = r.vert_wall_hit_x;
		_map()->rays[column].wall_hit_y = r.vert_wall_hit_y;
		_map()->rays[column].was_hit_vertical = TRUE;
	}
	else
	{
		_map()->rays[column].distance = r.horz_hit_distance;
		_map()->rays[column].wall_hit_x = r.horz_wall_hit_x;
		_map()->rays[column].wall_hit_y = r.horz_wall_hit_y;
		_map()->rays[column].was_hit_vertical = FALSE;
	}
	_map()->rays[column].ray_angle = r.ray_angle;
	_map()->rays[column].is_ray_facing_down = r.ray_is_facing_down;
	_map()->rays[column].is_ray_facing_up = r.ray_is_facing_up;
	_map()->rays[column].is_ray_facing_left = r.ray_is_facing_left;
	_map()->rays[column].is_ray_facing_right = r.ray_is_facing_right;
}

void	cast_all_rays(void)
{
	float	ray_angle;
	int		column;

	column = 0;
	while (column < NUM_RAYS)
	{
		ray_angle = _map()->plyr.rot_angle
			+ atan((column - NUM_RAYS / 2) / _map()->dist_proj_plane);
		cast_ray(ray_angle, column);
		column++;
	}
}
