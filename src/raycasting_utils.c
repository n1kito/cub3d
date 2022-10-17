#include "cub3D.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

//TODO replace player starting with 0 when parsing map?
int map_has_wall_at(float x, float y)
{
	if (x < 0 || x > 200000 || y < 0 || y > 200000) {
		return TRUE;
	}
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);
	if (mapGridIndexY > _map()->map_height -1 ) // TODO fix
		return 1;
	if (_map()->map[mapGridIndexY][mapGridIndexX] == '1')
		return (1);
	return (0);
}
