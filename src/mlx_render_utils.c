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
	if (x > WINDOW_WIDTH || x < 0)
		return ;
	if (y > WINDOW_HEIGHT || y < 0)
		return ;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void     ft_put_rectangle(t_img *img, int color)
{
    int pY;
    int pX;

    pY = _map()->coord->y0;
    while (pY < _map()->coord->y0 + _map()->coord->x1)
    {
        pX = _map()->coord->x0;
        while (pX < _map()->coord->x0 + _map()->coord->y1)
            ft_pixel_put(img, pX++, pY, color);
        pY++;
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
