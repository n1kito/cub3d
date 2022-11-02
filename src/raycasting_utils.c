/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:02 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 11:09:35 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	normalize_angle(float angle)
{
	angle = remainderf(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/* Checks if the coordinates correspond to a wall on the map. */
int	wall_at(float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > _map()->map_width * TILE_SIZE
		|| y < 0 || y > _map()->map_height * TILE_SIZE)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_y > _map()->map_height - 1)
		return (TRUE);
	if (map_grid_index_x > (int)ft_strlen(_map()->map[map_grid_index_y]))
		return (TRUE);
	if (_map()->map[map_grid_index_y][map_grid_index_x] == '1')
		return (TRUE);
	return (FALSE);
}

/* Initializes coord structure. Used before rendering shapes. */
void	coords_init(int x0, int y0, int x1, int y1)
{
	_map()->coord.x0 = x0;
	_map()->coord.y0 = y0;
	_map()->coord.x1 = x1;
	_map()->coord.y1 = y1;
}

void	update_pos(float new_pos[2], float new_x, float new_y)
{
	new_pos[0] = new_x;
	new_pos[1] = new_y;
}
