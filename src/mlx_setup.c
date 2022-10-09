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

int    move_player(int key, void *param)
{
    (void)param;
    if (key == UP)
    {
        _map()->player_position[1]--;
    }
    // update_POV();
    // update_minimap();
    render_minimap(_map()->graphics, _map()->map);
    mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
    return (0);
}

void    init_hooks(void)
{
    // Initialise player position to center of start position square
    _map()->player_position[0] = _map()->params->pl_start_pos[0] * _map()->graphics->minimap_tile + _map()->graphics->minimap_tile / 2;
    _map()->player_position[1] = _map()->params->pl_start_pos[1] * _map()->graphics->minimap_tile + _map()->graphics->minimap_tile / 2;
    _map()->graphics->minimap_img.image = mlx_new_image(_map()->graphics->mlx_ptr, _map()->graphics->minimap_width, _map()->graphics->minimap_height);
    // TODO protect
    // TODO move minimap rendering
    _map()->graphics->minimap_img.addr = mlx_get_data_addr(_map()->graphics->minimap_img.image, &_map()->graphics->minimap_img.bpp, &_map()->graphics->minimap_img.line_length, &_map()->graphics->minimap_img.endian);
    render_minimap(_map()->graphics, _map()->map);
    // render_player_position();
    mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
    // exit when pressing X
    mlx_key_hook(_map()->graphics->window_ptr, &move_player, NULL);
    mlx_loop_hook(_map()->graphics->window_ptr, &update_window, NULL);
    mlx_hook(_map()->graphics->window_ptr, 17, 0L, exit_game, NULL);

}