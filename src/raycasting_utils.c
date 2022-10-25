/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:02 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 09:22:03 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3D.h"
#include "../include/cub3D.h" //TODO REMOVE THIS

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
int	map_has_wall_at(float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > 200000 || y < 0 || y > 200000)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_y > _map()->map_height - 1)
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
