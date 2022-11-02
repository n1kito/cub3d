/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:12 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 11:04:11 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Called everytime a pointer to the main map structure is needed.
 * Initializes said map structure only on first call. */
t_map	*_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			exit(error_print("malloc fail [_map()]", 1));
		map_struct_init(map);
	}
	return (map);
}

/* Allocated memory for all elements of map structure
 * and initializes all pointers. */
void	map_struct_init(t_map *map)
{
	float	fov;

	fov = 60 * (PI / 180);
	map->map_name = NULL;
	map->file_contents = NULL;
	map->map = NULL;
	map->map_fd = -1;
	map->params = NULL;
	map->graphics = NULL;
	map->plyr.rot_angle = 0;
	map->plyr.rot = 0;
	map->plyr.move = 0;
	map->plyr.side = 0;
	map->plyr.mode_dell = 0;
	map->plyr.rot_speed = 0.09;
	map->plyr.mv_speed = 5;
	map->is_minimap_open = 0;
	map->dist_proj_plane = (WINDOW_WIDTH / 2) / tan(fov / 2);
	coords_init(0, 0, 0, 0);
	params_struct_init(map);
	graphics_struct_init(map);
}

/* Initialize all pointers in parameter structure. */
void	params_struct_init(t_map *map)
{
	map->params = malloc(sizeof(t_params));
	if (!map->params)
		ft_exit("malloc fail [map_struct_init()][1]", 1);
	map->params->n_texture.image = NULL;
	map->params->n_texture.path = NULL;
	map->params->s_texture.image = NULL;
	map->params->s_texture.path = NULL;
	map->params->e_texture.image = NULL;
	map->params->e_texture.path = NULL;
	map->params->w_texture.image = NULL;
	map->params->w_texture.path = NULL;
	map->params->c_rgb_color[0] = -1;
	map->params->f_rgb_color[0] = -1;
	map->params->pl_start_pos[0] = -1;
	map->params->pl_start_pos[1] = -1;
}

/* Initialize all pointers in graphics structure. */
void	graphics_struct_init(t_map *map)
{
	map->graphics = malloc(sizeof(t_mlx));
	if (!map->graphics)
		ft_exit("malloc fail [map_struct_init()][2]", 1);
	map->graphics->mlx_ptr = NULL;
	map->graphics->window_ptr = NULL;
	map->graphics->minimap_width = 11 * MINI_TILE;
	map->graphics->minimap_height = map->graphics->minimap_width;
	map->graphics->game_img.image = NULL;
	map->graphics->minimap_img.image = NULL;
}
