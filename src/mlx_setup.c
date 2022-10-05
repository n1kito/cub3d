#include "cub3D.h"
#include <math.h> // TODO move to header

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

void    ft_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    //TODO research to understand this formula cf aurelienbrabant.fr
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(int *)pixel = color;
}

int     color_generator(u_int8_t red, u_int8_t green, u_int8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

int     ft_put_rectangle(t_img *img, int x, int y, int height, int width, int color)
{
    int i;
    int j;

    i = y;
    while (i < y + height)
    {
        j = x;
        while (j < x + width)
            ft_pixel_put(img, j++, i, color);
        i++;
    }
    return (0);
}

void    ft_draw_circle(t_img *img, int x, int y, int radius, int color)
{
    double angle;
    double dot_x;
    double dot_y;

    while (radius)
    {  
        angle = 0;
        while (angle < 360)
        {
         dot_x = cos(angle) * (double)radius;
         dot_y = sin(angle) * (double)radius;
        //  ft_draw_line(img, x, y, x + dot_x, y + dot_y, color); // TODO ecrire cette fonction et savoir comment elle marche
         ft_pixel_put(img, x + (int)dot_x, y + (int)dot_y, color);
         angle++;
        }
        radius--;
    }
}

void    render_minimap()
{
    int draw_pos_x;
    int draw_pos_y;
    int draw_end_x;
    int draw_end_y;
    int minimap_x;
    int minimap_y;
    int dot_pos[2];

    ft_put_rectangle(&_map()->graphics->minimap_img, 0, 0, _map()->graphics->minimap_height, _map()->graphics->minimap_width, color_generator(0, 0, 0));
    draw_pos_x = 0;
    draw_pos_y = 0;
    if (_map()->player_position[0] / _map()->graphics->minimap_tile >= 5)
        draw_pos_x = (_map()->player_position[0] / _map()->graphics->minimap_tile) - 5;
    if (_map()->player_position[1] / _map()->graphics->minimap_tile >= 5)
        draw_pos_y = (_map()->player_position[1] / _map()->graphics->minimap_tile) - 5;
    draw_end_x = draw_pos_x + 10;
    draw_end_y = draw_pos_y + 10;
    minimap_y = 0;
    while (draw_pos_y < draw_end_y && _map()->map[draw_pos_y])
    {
        draw_pos_x = draw_end_x - 10;
        minimap_x = 0;
        while (draw_pos_x < draw_end_x && _map()->map[draw_pos_y][draw_pos_x])
        {
            // if (_map()->map[draw_pos_y][draw_pos_x] == '0')
            if (_map()->map[draw_pos_y][draw_pos_x] == '0' || is_start_position(_map()->map[draw_pos_y][draw_pos_x]))
                ft_put_rectangle(&_map()->graphics->minimap_img, minimap_x * _map()->graphics->minimap_tile + 0.5, minimap_y * _map()->graphics->minimap_tile + 0.5, _map()->graphics->minimap_tile - 1, _map()->graphics->minimap_tile - 1, color_generator(255, 225, 255));
            // else if (is_start_position(_map()->map[draw_pos_y][draw_pos_x]))
                // ft_put_rectangle(&_map()->graphics->minimap_img, minimap_x * _map()->graphics->minimap_tile + 0.5, minimap_y * _map()->graphics->minimap_tile + 0.5, _map()->graphics->minimap_tile - 1, _map()->graphics->minimap_tile - 1, color_generator(255, 0, 0));
            else if (_map()->map[draw_pos_y][draw_pos_x] == '1')
                ft_put_rectangle(&_map()->graphics->minimap_img, minimap_x * _map()->graphics->minimap_tile + 0.5, minimap_y * _map()->graphics->minimap_tile + 0.5, _map()->graphics->minimap_tile - 1, _map()->graphics->minimap_tile - 1, color_generator(192, 192, 255));    
            draw_pos_x++;
            minimap_x++;
        }
        draw_pos_y++;
        minimap_y++;
    }
    dot_pos[0] = _map()->player_position[0] - (draw_end_x - 10) * _map()->graphics->minimap_tile - 1;
    dot_pos[1] = _map()->player_position[1] - (draw_end_y - 10) * _map()->graphics->minimap_tile - 1;
    ft_draw_circle(&_map()->graphics->minimap_img, dot_pos[0], dot_pos[1], 7, color_generator(255, 0, 0));
    // ft_put_rectangle(&_map()->graphics->minimap_img, dot_pos[0], dot_pos[1], 5, 5, color_generator(255, 0, 0));
} 

void    init_hooks(void)
{
    // Initialise player position to center of start position square
    _map()->player_position[0] = _map()->params->pl_start_pos[0] * _map()->graphics->minimap_tile + _map()->graphics->minimap_tile / 2;
    _map()->player_position[1] = _map()->params->pl_start_pos[1] * _map()->graphics->minimap_tile + _map()->graphics->minimap_tile / 2;
    // END 
    _map()->graphics->minimap_img.image = mlx_new_image(_map()->graphics->mlx_ptr, _map()->graphics->minimap_width, _map()->graphics->minimap_height);
    // TODO protect
    _map()->graphics->minimap_img.addr = mlx_get_data_addr(_map()->graphics->minimap_img.image, &_map()->graphics->minimap_img.bpp, &_map()->graphics->minimap_img.line_length, &_map()->graphics->minimap_img.endian);
    render_minimap();
    // render_player_position();
    mlx_put_image_to_window(_map()->graphics->mlx_ptr, _map()->graphics->window_ptr, _map()->graphics->minimap_img.image, _map()->graphics->minimap_tile, _map()->graphics->minimap_tile);
    mlx_hook(_map()->graphics->window_ptr, 17, 0L, exit_game, NULL);
}