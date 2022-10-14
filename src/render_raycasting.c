#include "cub3D.h"

void	cast_ray(float ray_angle, int strip_id)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down;
	int is_ray_facing_up;
	int is_ray_facing_right;
	int is_ray_facing_left;

	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	is_ray_facing_up = !is_ray_facing_down;
	is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	is_ray_facing_left = !is_ray_facing_right;

	float xintercept, yintercept;
	float xstep, ystep;

	// HORIZONTAL RAY-GRID INTERSECTION
	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;

	yintercept = floor(_map()->plyr.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down)
		yintercept += TILE_SIZE;

	xintercept = _map()->plyr.x + (yintercept - _map()->plyr.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	if (is_ray_facing_up)
		ystep *= -1;

	xstep = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_left && xstep > 0)
		xstep *= -1;
	if (is_ray_facing_right && xstep < 0)
		xstep *= -1;

	float next_horz_touch_x = xintercept;
	float next_horz_touch_y = yintercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		float   x_to_check = next_horz_touch_x;
		float   y_to_check = next_horz_touch_y;
		if (is_ray_facing_up)
			y_to_check -= 1;
		else
			y_to_check = next_horz_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	// VERTICAL WALL HIT INTERSECTION
	int found_vert_wall_hit = FALSE;
	float   vert_wall_hit_x = 0;
	float   vert_wall_hit_y = 0;

	xintercept = floor(_map()->plyr.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right)
		xintercept += TILE_SIZE;

	yintercept = _map()->plyr.y + (xintercept - _map()->plyr.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	if (is_ray_facing_left)
		xstep *= -1;

	ystep = TILE_SIZE * tan(ray_angle);
	if (is_ray_facing_up && ystep > 0)
		ystep *= -1;
	if (is_ray_facing_down && ystep < 0)
		ystep *= -1;

	float next_vert_touch_x = xintercept;
	float next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float   x_to_check = next_vert_touch_x;
		if (is_ray_facing_left)
			x_to_check -= 1;
		float   y_to_check = next_vert_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	// Calculate vertical and horizontal wall hit distances and pick the smaller one
	float horz_hit_distance;
	float vert_hit_distance;

	if (found_horz_wall_hit)
		horz_hit_distance = distance_between_points(_map()->plyr.x, _map()->plyr.y, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = (float)INT_MAX;
	if (found_vert_wall_hit)
		vert_hit_distance = distance_between_points(_map()->plyr.x, _map()->plyr.y, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = (float)INT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		_map()->rays[strip_id].distance = vert_hit_distance;
		_map()->rays[strip_id].wall_hit_x = vert_wall_hit_x;
		_map()->rays[strip_id].wall_hit_y = vert_wall_hit_y;
		_map()->rays[strip_id].was_hit_vertical = TRUE;

	}
	else
	{
		_map()->rays[strip_id].distance = horz_hit_distance;
		_map()->rays[strip_id].wall_hit_x = horz_wall_hit_x;
		_map()->rays[strip_id].wall_hit_y = horz_wall_hit_y;
		_map()->rays[strip_id].was_hit_vertical = FALSE;
	}
	_map()->rays[strip_id].ray_angle = ray_angle;
	_map()->rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	_map()->rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	_map()->rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	_map()->rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void	cast_all_rays(void)
{
	float   ray_angle;
	int	 strip_ID;

	ray_angle = _map()->plyr.rot_angle - (FOV / 2);
	strip_ID = 0;
	while (strip_ID < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_ID);
		ray_angle += FOV / NUM_RAYS;
		strip_ID++;
	}
}

void	render_rays(void)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		if (i % 1 == 0)
		{
			// coords_init(SCALE_FACTOR * _map()->plyr.x,
			// 			SCALE_FACTOR * _map()->plyr.y,
			// 			SCALE_FACTOR * _map()->rays[i].wall_hit_x,
			// 			SCALE_FACTOR * _map()->rays[i].wall_hit_y);
			// ft_draw_line(&_map()->graphics->minimap_img, BLUE);
//			if (i == 0 || i == WINDOW_WIDTH -1)
//			{
				coords_init(SCALE_FACTOR * _map()->plyr.x,
				SCALE_FACTOR * _map()->plyr.y,
				SCALE_FACTOR * _map()->rays[i].wall_hit_x,
				SCALE_FACTOR * _map()->rays[i].wall_hit_y);
			ft_draw_line(&_map()->graphics->minimap_img, BLUE);
//			}
//			coords_init(SCALE_FACTOR * _map()->rays[i].wall_hit_x,
//			SCALE_FACTOR * _map()->rays[i].wall_hit_y,
//			5,
//			5);
//			ft_put_rectangle(&_map()->graphics->minimap_img, BLUE);
		}
		i++;
	}
}

void	generate_proj(void)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		float projectedWallHeight = (TILE_SIZE / _map()->rays[i].distance * distanceProjPlane);

		int	wallStripHeight = (int)projectedWallHeight;
		// fixing slow down when facing wall a little too close
		if (wallStripHeight > WINDOW_HEIGHT)
			wallStripHeight = WINDOW_HEIGHT;
		
		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel < 0 ? 0 : wallBottomPixel;

		coords_init(i, 0, wallTopPixel, 1);
		ft_put_rectangle(&_map()->graphics->game_img, TEAL);
		
		coords_init(i, wallTopPixel, wallBottomPixel - wallTopPixel, 1);
		ft_put_rectangle(&_map()->graphics->game_img, GREY);

		coords_init(i, wallBottomPixel, WINDOW_HEIGHT - wallBottomPixel, 1);
		ft_put_rectangle(&_map()->graphics->game_img, PURPLE);
		i++;

	}
}
