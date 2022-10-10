#include "cub3D.h"

// void    render_minimap(t_mlx *g, char **map)
// {
//     int      pos[2];
//     int      lim[2];
//     int      minimap[2];

//     coords_init(0, 0, g->minimap_height, g->minimap_width);
//     ft_put_rectangle(&g->minimap_img, BLACK);
//     init_minimap_values(pos, lim);
//     minimap[1] = 0;
//     while (pos[1] < lim[1] && _map()->map[pos[1]])
//     {
//         pos[0] = lim[0] - 10;
//         minimap[0] = 0;
//         while (pos[0] < lim[0] && map[pos[1]][pos[0]])
//         {
//             if (map[pos[1]][pos[0]] == '0' || is_start_position(map[pos[1]][pos[0]]))
//             {
//                 coords_init(minimap[0] * g->minimap_tile + 0.5,
//                     minimap[1] * g->minimap_tile + 0.5, g->minimap_tile - 1, g->minimap_tile - 1);
//                 ft_put_rectangle(&g->minimap_img, WHITE);
//             }
//             else if (map[pos[1]][pos[0]] == '1')
//             {
//                 coords_init(minimap[0] * g->minimap_tile + 0.5,
//                     minimap[1] * g->minimap_tile + 0.5, g->minimap_tile - 1, g->minimap_tile - 1);
//                 ft_put_rectangle(&g->minimap_img, GREY);    
//             }
//             pos[0]++;
//             minimap[0]++;
//         }
//         pos[1]++;
//         minimap[1]++;
//     }
//     render_player_dot_on_minimap(lim);
// } 

// void    render_player_dot_on_minimap(int *draw_end)
// {
//     int     dot_pos[2];
//     int     tile_size;
//     t_img   minimap_img;

//     tile_size = _map()->graphics->minimap_tile;
//     minimap_img = _map()->graphics->minimap_img;
//     dot_pos[0] = _map()->plyr.pos[0] - (draw_end[0] - 10) * tile_size - 1;
//     dot_pos[1] = _map()->plyr.pos[1] - (draw_end[1] - 10) * tile_size- 1;
//     ft_put_circle(&minimap_img, dot_pos[0], dot_pos[1], tile_size * 0.5 / 2, RED);
// }

// void    init_minimap_values(int *draw_pos, int *draw_end)
// {
//     draw_pos[0] = 0;
//     draw_pos[1] = 0;
//     if (_map()->plyr.pos[0] / _map()->graphics->minimap_tile >= 5)
//         draw_pos[0] = (_map()->plyr.pos[0] / _map()->graphics->minimap_tile) - 5;
//     if (_map()->plyr.pos[1] / _map()->graphics->minimap_tile >= 5)
//         draw_pos[1] = (_map()->plyr.pos[1] / _map()->graphics->minimap_tile) - 5;
//     draw_end[0] = _map()->map_width;
//     draw_end[1] = _map()->map_height;
// }

void    render_minimap(t_mlx *g, char **map)
{
    int      pos[2];
    int      lim[2];
    int      minimap[2];

    coords_init(0, 0, g->minimap_height, g->minimap_width);
    ft_put_rectangle(&g->minimap_img, BLACK);
    init_minimap_values(pos, lim);
    minimap[1] = 0;
    while (pos[1] < lim[1] && _map()->map[pos[1]])
    {
        pos[0] = lim[0] - 10;
        minimap[0] = 0;
        while (pos[0] < lim[0] && map[pos[1]][pos[0]])
        {
            if (map[pos[1]][pos[0]] == '0' || is_start_position(map[pos[1]][pos[0]]))
            {
                coords_init(minimap[0] * g->minimap_tile + 0.5,
                    minimap[1] * g->minimap_tile + 0.5, g->minimap_tile - 1, g->minimap_tile - 1);
                ft_put_rectangle(&g->minimap_img, WHITE);
            }
            else if (map[pos[1]][pos[0]] == '1')
            {
                coords_init(minimap[0] * g->minimap_tile + 0.5,
                    minimap[1] * g->minimap_tile + 0.5, g->minimap_tile - 1, g->minimap_tile - 1);
                ft_put_rectangle(&g->minimap_img, GREY);    
            }
            pos[0]++;
            minimap[0]++;
        }
        pos[1]++;
        minimap[1]++;
    }
    render_player_dot_on_minimap(lim);
} 

void    render_player_dot_on_minimap(int *draw_end)
{
    int     dot_pos[2];
    int     tile_size;
    t_img   minimap_img;

    tile_size = _map()->graphics->minimap_tile;
    minimap_img = _map()->graphics->minimap_img;
    dot_pos[0] = _map()->plyr.x - (draw_end[0] - 10) * tile_size - 1;
    dot_pos[1] = _map()->plyr.y - (draw_end[1] - 10) * tile_size- 1;
    ft_put_circle(&minimap_img, dot_pos[0], dot_pos[1], tile_size * 0.5 / 5, RED);
    coords_init(dot_pos[0], dot_pos[1], dot_pos[0] + cos(_map()->plyr.rot_angle) * 40, dot_pos[1] + sin(_map()->plyr.rot_angle) * 40);
    ft_draw_line(&minimap_img, RED);
}

void    init_minimap_values(int *draw_pos, int *draw_end)
{
    draw_pos[0] = 0;
    draw_pos[1] = 0;
    if (_map()->plyr.x / _map()->graphics->minimap_tile >= 5)
        draw_pos[0] = (_map()->plyr.x / _map()->graphics->minimap_tile) - 5;
    if (_map()->plyr.y / _map()->graphics->minimap_tile >= 5)
        draw_pos[1] = (_map()->plyr.y / _map()->graphics->minimap_tile) - 5;
    draw_end[0] = draw_pos[0] + 10;
    draw_end[1] = draw_pos[1] + 10;
}