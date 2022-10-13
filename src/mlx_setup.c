#include "cub3D.h"

void    mlx_setup(void)
{
    t_map   *m;
    t_mlx   *g;

    m = _map();
    g = m->graphics;
    g->mlx_ptr = mlx_init();
    if (!g->mlx_ptr)
        ft_exit("mlx_init() fail [mlx_setup()]", 1);
    g->window_ptr = mlx_new_window(g->mlx_ptr,
        g->window_width, g->window_height,
        m->map_name);
    if (!g->window_ptr)
        ft_exit("failed to create window [mlx_setup()]", 1);   
    g->minimap_img.image = mlx_new_image(g->mlx_ptr, g->minimap_width, g->minimap_height);
    if (!g->minimap_img.image)
        ft_exit("failed to create minimap image", 1);
}

int     exit_game()
{
    ft_exit(NULL, 0);
    exit(0);
}

int    key_press(int key, void *param)
{
    (void)param;
    if (key == UP)
        _map()->plyr.move = 1;
    else if (key == DOWN)
        _map()->plyr.move = -1;
    else if (key == LEFT)
        _map()->plyr.move = 2;
    else if (key == RIGHT)
        _map()->plyr.move = -2;
    else if (key == ARROW_LEFT)
        _map()->plyr.rot = -1;
    else if (key == ARROW_RIGHT)
        _map()->plyr.rot = 1;
    else if (key == ESC)
        exit_game();
    // update_POV();
    // update_minimap();
    return (0);
}

int key_release(int key, void *param)
{
    (void)param;
    if (key == UP)
        _map()->plyr.move = 0;
    else if (key == DOWN)
        _map()->plyr.move = 0;
    if (key == LEFT)
        _map()->plyr.move = 0;
    if (key == RIGHT)
        _map()->plyr.move = 0;
    else if (key == ARROW_LEFT)
        _map()->plyr.rot = 0;
    else if (key == ARROW_RIGHT)
        _map()->plyr.rot = 0;
    return (0);
}

float   normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return (angle);
}

// IDEM je l'ai piquee a pikuma mais en gros copie colle
float distance_between_points(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

//TODO replace player starting with 0 when parsing map?
int map_has_wall_at(float x, float y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return TRUE;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
	// printf("%d\n", ft_tabsize(_map()->map));
	if (mapGridIndexY > _map()->map_height -1 ) // TODO fix
	 return 1; 
	// printf("map char: %c, on [%d][%d]\n", _map()->map[mapGridIndexY][mapGridIndexX], mapGridIndexY, mapGridIndexX);
    if (_map()->map[mapGridIndexY][mapGridIndexX] == '1')
		return (1);
	return (0);
}

void    cast_ray(float ray_angle, int strip_id)
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

void    cast_all_rays()
{
    float   ray_angle;
    int     strip_ID;

    ray_angle = _map()->plyr.rot_angle - (FOV / 2);
    strip_ID = 0;
    while (strip_ID < NUM_RAYS)
    {
        cast_ray(ray_angle, strip_ID);
        ray_angle += FOV / NUM_RAYS;
        strip_ID++;
    }
}

void    render_rays()
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
			if (i == 0 || i == WINDOW_WIDTH -1)
			{
				coords_init(SCALE_FACTOR * _map()->plyr.x, 
				SCALE_FACTOR * _map()->plyr.y,
				SCALE_FACTOR * _map()->rays[i].wall_hit_x,
				SCALE_FACTOR * _map()->rays[i].wall_hit_y);
			ft_draw_line(&_map()->graphics->minimap_img, BLUE);
			}
			coords_init(SCALE_FACTOR * _map()->rays[i].wall_hit_x, 
			SCALE_FACTOR * _map()->rays[i].wall_hit_y,
			5,
			5);
			ft_put_rectangle(&_map()->graphics->minimap_img, BLUE);
		}
        i++;
    }
}

void	generate_proj(void)
{
	int	i;

	i = 0;
	printf("Dist : %f\n", _map()->rays[960].distance);
	while (i < NUM_RAYS)
	{
		float perpDistance = _map()->rays[i].distance * cos(_map()->rays[i].ray_angle - _map()->plyr.rot_angle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

		int	wallStripHeight = (int)projectedWallHeight;
		
		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel < 0 ? 0 : wallBottomPixel;

		
		if (_map()->rays[i].distance < 96)
		{
			coords_init(i, 0, wallTopPixel, 1);
			ft_put_rectangle(&_map()->graphics->game_img, PLA_1);
			coords_init(i, wallTopPixel, wallBottomPixel - wallTopPixel, 1);
			if (_map()->rays[i].was_hit_vertical)
				ft_put_rectangle(&_map()->graphics->game_img, XMUR_1);
			else
				ft_put_rectangle(&_map()->graphics->game_img, YMUR_1);
			coords_init(i, wallBottomPixel, WINDOW_HEIGHT - wallBottomPixel, 1);
			ft_put_rectangle(&_map()->graphics->game_img, SOL_1);
		}
		else if (_map()->rays[i].distance >= 96 /*&& _map()->rays[WINDOW_WIDTH / 2].distance < 160*/)
		{
			coords_init(i, 0, wallTopPixel, 1);
			ft_put_rectangle(&_map()->graphics->game_img, PLA_1);
			coords_init(i, wallTopPixel, wallBottomPixel - wallTopPixel, 1);
			if (_map()->rays[i].was_hit_vertical)
				ft_put_rectangle(&_map()->graphics->game_img, XMUR_2);
			else
				ft_put_rectangle(&_map()->graphics->game_img, YMUR_2);
			coords_init(i, wallBottomPixel, WINDOW_HEIGHT - wallBottomPixel, 1);
			ft_put_rectangle(&_map()->graphics->game_img, SOL_1);
		}
		i++;

	}
}

void	move_player(void)
{
	float	new_x;
	float	new_y;

    _map()->plyr.rot_angle += _map()->plyr.rot * 0.09;
    new_x = (_map()->plyr.x + (cos(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
    new_y = (_map()->plyr.y + (sin(_map()->plyr.rot_angle) * _map()->plyr.move) * 5);
	if (!map_has_wall_at(new_x, new_y))
	{
		_map()->plyr.x = new_x;
		_map()->plyr.y = new_y;
	}
}

int update_window(void)
{
	move_player();
    cast_all_rays();
    render_minimap(_map()->graphics, _map()->map);
    render_rays();
	generate_proj();
    mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->game_img.image, 0, 0);
    mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
	return (0);
}

void    init_hooks(void)
{

    // Initialise player position to center of start position square
    _map()->plyr.x = _map()->params->pl_start_pos[0] * TILE_SIZE + TILE_SIZE / 2;
    _map()->plyr.y = _map()->params->pl_start_pos[1] * TILE_SIZE + TILE_SIZE / 2;
    _map()->graphics->minimap_img.image = mlx_new_image(_map()->graphics->mlx_ptr, _map()->graphics->minimap_width, _map()->graphics->minimap_height);
    _map()->graphics->game_img.image = mlx_new_image(_map()->graphics->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// TODO protect
    // TODO move minimap rendering
    _map()->graphics->minimap_img.addr = mlx_get_data_addr(_map()->graphics->minimap_img.image, &_map()->graphics->minimap_img.bpp, &_map()->graphics->minimap_img.line_length, &_map()->graphics->minimap_img.endian);
    _map()->graphics->game_img.addr = mlx_get_data_addr(_map()->graphics->game_img.image, &_map()->graphics->game_img.bpp, &_map()->graphics->game_img.line_length, &_map()->graphics->game_img.endian);
	// render_minimap(_map()->graphics, _map()->map);
    // render_player_position();
    // mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
    // exit when pressing X
    mlx_hook(_map()->graphics->window_ptr, 17, 0L, exit_game, NULL);
    // mlx_key_hook(_map()->graphics->window_ptr, &move_player, NULL);
    mlx_hook(_map()->graphics->window_ptr, 2, 1L << 0, key_press, NULL);
    mlx_hook(_map()->graphics->window_ptr, 3, 1L << 1, key_release, NULL);
	// update_window();
    mlx_loop_hook(_map()->graphics->mlx_ptr, &update_window, NULL);
}