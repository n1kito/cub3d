#include "cub3D.h"

void    coords_init(int x0, int y0, int x1, int y1)
{
    _map()->coord = malloc(sizeof(t_coord));
    // if (!_map()->coord)
    //     jsp
    _map()->coord->x0 = x0;
    _map()->coord->y0 = y0;
    _map()->coord->x1 = x1;
    _map()->coord->y1 = y1;
}

void    free_coords()
{
    free(_map()->coord);
    _map()->coord = NULL;
}