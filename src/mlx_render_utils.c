#include "cub3D.h"

/* Returns an int containing the RGB color values passed as parameter. */
int     color_generator(u_int8_t red, u_int8_t green, u_int8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

void    ft_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    //TODO research to understand this formula cf aurelienbrabant.fr
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void     ft_put_rectangle(t_img *img, int color)
{
    int i;
    int j;

    i = _map()->coord->y0;
    while (i < _map()->coord->y0 + _map()->coord->x1)
    {
        j = _map()->coord->x0;
        while (j < _map()->coord->x0 + _map()->coord->y1)
            ft_pixel_put(img, j++, i, color);
        i++;
    }
    free_coords();
}

/* Displays a filled in ellipse on image. */
void    ft_put_circle(t_img *img, int x, int y, int radius, int color)
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
            ft_pixel_put(img, x + (int)dot_x, y + (int)dot_y, color);
            angle++;
        }
        radius--;
    }
}

// TODO comprendre 
// void ft_draw_line(t_img *img, int color)
// {
//     int dx, dy, p;
 
//     dx = _map()->coord->x1 - _map()->coord->x0;
//     dy = _map()->coord->y1 - _map()->coord->y0;
//     p = 2 * dy - dx;
//     while (_map()->coord->x0 < _map()->coord->x1)
//     {
//         if (p >= 0)
//         {
//             ft_pixel_put(img, _map()->coord->x0, _map()->coord->y0, color);
//             _map()->coord->y0 = _map()->coord->y0 + 1;
//             p = p + 2 * dy - 2 * dx;
//         }
//         else
//         {
//             ft_pixel_put(img, _map()->coord->x0, _map()->coord->y0, color);
//             p = p + 2 * dy;
//         }
//         _map()->coord->x0 = _map()->coord->x0 + 1;
//     }
//     free_coords();
// }

void ft_draw_line(t_img *img, int color)
{
    double dx, dy, pX, pY;
    int p;

    dx = _map()->coord->x1 - _map()->coord->x0;
    dy = _map()->coord->y1 - _map()->coord->y0;
    p = sqrt((dx * dx) + (dy * dy));
    dx /= p;
    dy /= p;
    pX = _map()->coord->x0;
    pY = _map()->coord->y0;
    while (p)
    {
        ft_pixel_put(img, pX, pY, color);
        pX += dx;
        pY += dy;
        --p;
    }
    free_coords();
}














// void bresenham(int x1, int y1, int x2, int y2) {    
//     int dx = x2 - x1;
//     int dy = y2 - y1;

//     int error;
//     /** first quarter */
//     if(dx >= 0 && dy >= 0) {
//         /** 1st octant */
//         if (dx >= dy) {
//             error = -dx;
//             int y = y1;
//             for(int x = x1; x < x2; x++) {
//                 draw_pixel(x, y);
//                 error = error + 2 * dy;
//                 if (error >= 0) {
//                     y++;
//                     error = error - 2 * dx;
//                 }
//             }
//         }
//         /** 2nd octant */
//         else {
//             error = -dy;
//             int x = x1;
//             for(int y = y1; y < y2; y++) {
//                 draw_pixel(x, y);
//                 error = error + 2 * dx;
//                 if (error >= 0) {
//                     x++;
//                     error = error - 2 * dy ;
//                 }
//             }
//         }
//     }
//     /** second quarter */
//     else if (dx <= 0 && dy >= 0) {
//         /** 4th octant */
//         if(dx < -dy) {
//             error = dx;
//             int y = y1;
//             for(int x = x1; x > x2; x--) {
//                 draw_pixel(x, y);
//                 error = error + 2 * dy;
//                 if (error >= 0) {
//                     y++;
//                     error = error + 2 * dx;
//                 }
//             }
//         }
//         /** 3rd octant */
//         else {
//             error = -dy;
//             int x = x1;
//             for(int y = y1; y < y2; y++) {
//                 draw_pixel(x, y);
//                 error = error - 2 * dx;
//                 if (error >= 0) {
//                     x--;
//                     error = error - 2 * dy;
//                 }
//             }
//         }
//     }
//     /** 3rd quarter */
//     else if (dx <= 0 && dy <= 0) {
//         /** 5th octant */
//         if(dx <= dy) {
//             error = 2 * dx;
//             int y = y1;
//             for(int x = x1; x > x2; x--) {
//                 draw_pixel(x, y);
//                 error = error - 2 * dy;
//                 if (error >= 0) {
//                     y--;
//                     error = error + 2 * dx;
//                 }
//             }
//         }
//         /** 6th octant */
//         else {
//             error = 2 * dy;
//             int x = x1;
//             for(int y = y1; y > y2; y--) {
//                 draw_pixel(x, y);
//                 error = error - 2 * dx;
//                 if (error >= 0) {
//                     x--;
//                     error = error + 2 * dy ;
//                 }
//             }
//         }
//     }
//     /* 4th quarter */
//     else if(dx >= 0 && dy <= 0) {
//         /** 7th octant */
//         if(dx < -dy) {
//             error = 2 * dy;
//             int x = x1;
//             for(int y = y1; y > y2; y--) {
//                 draw_pixel(x, y);
//                 error = error + 2 * dx;
//                 if (error >= 0) {
//                     x++;
//                     error = error + 2 * dy ;
//                 }
//             }
//         }
//         /** 8th octant */
//         else {
//             error = -dx;
//             int y = y1;
//             for(int x = x1; x < x2; x++) {
//                 draw_pixel(x, y);
//                 error = error - 2 * dy;
//                 if (error >= 0) {
//                     y--;
//                     error = error - 2 * dx;
//                 }
//             }
//         }
//     }
// }