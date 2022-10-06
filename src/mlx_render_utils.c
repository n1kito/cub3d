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

void     ft_put_rectangle(t_img *img, int x, int y, int height, int width, int color)
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
        //  ft_draw_line(img, x, y, x + dot_x, y + dot_y, color); // TODO ecrire cette fonction et savoir comment elle marche
         ft_pixel_put(img, x + (int)dot_x, y + (int)dot_y, color);
         angle++;
        }
        radius--;
    }
}