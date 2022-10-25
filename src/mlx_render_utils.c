/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:09 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:15:09 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Places pixel of color on image. */
void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > WINDOW_WIDTH || x < 0)
		return ;
	if (y > WINDOW_HEIGHT || y < 0)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)pixel = color;
}

/* Places rectangle in image. Needs coords struct to be set first. */
void	ft_put_rectangle(t_img *img, int color)
{
	int	position_x;
	int	position_y;

	position_y = _map()->coord.y0;
	while (position_y < _map()->coord.y0 + _map()->coord.x1)
	{
		position_x = _map()->coord.x0;
		while (position_x < _map()->coord.x0 + _map()->coord.y1)
			ft_pixel_put(img, position_x++, position_y, color);
		position_y++;
	}
}

/* Displays a filled in ellipse on image. */
void	ft_put_circle(t_img *img, double pos[2], int radius, int color)
{
	double	angle;
	double	dot_x;
	double	dot_y;

	while (radius)
	{
		angle = 0;
		while (angle < 360)
		{
			dot_x = cos(angle) * (double)radius;
			dot_y = sin(angle) * (double)radius;
			ft_pixel_put(img, pos[0] + (int)dot_x, pos[1] + (int)dot_y, color);
			angle++;
		}
		radius--;
	}
}

/* Draws line on image passed as parameter. */
void	ft_draw_line(t_img *img, int color)
{
	double	dist[2];
	double	pos[2];
	int		p;

	dist[0] = _map()->coord.x1 - _map()->coord.x0;
	dist[1] = _map()->coord.y1 - _map()->coord.y0;
	p = sqrt((dist[0] * dist[0]) + (dist[1] * dist[1]));
	dist[0] /= p;
	dist[1] /= p;
	pos[0] = _map()->coord.x0;
	pos[1] = _map()->coord.y0;
	while (p)
	{
		ft_pixel_put(img, pos[0], pos[1], color);
		pos[0] += dist[0];
		pos[1] += dist[1];
		--p;
	}
}
