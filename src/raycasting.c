//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

void	calculate_wall_hit_distances(t_raycasting *r)
{
	if (r->found_horz_wall_hit)
		r->horz_hit_distance = distance_between_points(_map()->plyr.x,
				_map()->plyr.y, r->horz_wall_hit_x, r->horz_wall_hit_y);
	else
		r->horz_hit_distance = (float)INT_MAX; // TODO REPLACE WITH FLOAT MAX
	if (r->found_vert_wall_hit)
		r->vert_hit_distance = distance_between_points(_map()->plyr.x,
				_map()->plyr.y, r->vert_wall_hit_x, r->vert_wall_hit_y);
	else
		r->vert_hit_distance = (float)INT_MAX; // TODO REPLACE WITH FLOAT MAX
}

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
		if (map_has_wall_at(r->x_to_check, r->y_to_check))
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
		if (map_has_wall_at(r->x_to_check, r->y_to_check))
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

void	cast_ray(float ray_angle, int strip_id)
{
	t_raycasting	r;

	init_raycasting_values(&r, ray_angle);
	find_horz_grid_intersection(&r);
	find_vert_grid_intersection(&r);
	calculate_wall_hit_distances(&r);
	if (r.vert_hit_distance < r.horz_hit_distance)
	{
		_map()->rays[strip_id].distance = r.vert_hit_distance;
		_map()->rays[strip_id].wall_hit_x = r.vert_wall_hit_x;
		_map()->rays[strip_id].wall_hit_y = r.vert_wall_hit_y;
		_map()->rays[strip_id].was_hit_vertical = TRUE;
	}
	else
	{
		_map()->rays[strip_id].distance = r.horz_hit_distance;
		_map()->rays[strip_id].wall_hit_x = r.horz_wall_hit_x;
		_map()->rays[strip_id].wall_hit_y = r.horz_wall_hit_y;
		_map()->rays[strip_id].was_hit_vertical = FALSE;
	}
	_map()->rays[strip_id].ray_angle = r.ray_angle;
	_map()->rays[strip_id].is_ray_facing_down = r.ray_is_facing_down;
	_map()->rays[strip_id].is_ray_facing_up = r.ray_is_facing_up;
	_map()->rays[strip_id].is_ray_facing_left = r.ray_is_facing_left;
	_map()->rays[strip_id].is_ray_facing_right = r.ray_is_facing_right;
}

void	cast_all_rays(void)
{
	float	ray_angle;
	int		strip_ID;

	ray_angle = _map()->plyr.rot_angle - (FOV / 2);
	strip_ID = 0;
	while (strip_ID < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_ID);
		ray_angle += FOV / NUM_RAYS;
		strip_ID++;
	}
}
