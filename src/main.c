/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:35 by mjallada          #+#    #+#             */
/*   Updated: 2022/10/25 14:13:44 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (error_print("map needed to launch ./cub3D", 1));
	_map();
	_map()->map_name = argv[1];
	map_file_checker();
	map_parsing();
	mlx_setup();
	init_hooks();
	mlx_loop(_map()->graphics->mlx_ptr);
	return (free_all(), 0);
}
