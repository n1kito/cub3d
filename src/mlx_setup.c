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
    
}