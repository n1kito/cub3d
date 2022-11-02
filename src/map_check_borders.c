/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:22:27 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 13:42:48 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_inside_map_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	print_map_unvalid_char(int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (_map()->map[x])
	{
		if (x == i)
		{
			ft_printf_fd(2, "%s", _map()->map[x]);
			if (_map()->map[x][ft_strlen(_map()->map[x]) - 1] != '\n')
				ft_printf_fd(2, "\n");
			while (++y < j)
				write(2, "-", 1);
			write(2, "^", 2);
			ft_printf_fd(2, "    Map not closed on [%d][%d] !\n", i, j);
		}
		else
			ft_printf_fd(2, "%s", _map()->map[x]);
		x++;
	}
	if (_map()->map[x - 1][ft_strlen(_map()->map[x - 1]) - 1] != '\n')
		ft_printf_fd(2, "\n");
}

void	check_if_inside_map(int i, int j)
{
	if (!_map()->map[i + 1])
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i + 1][j]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (i == 0 || !is_valid_map_char(_map()->map[i - 1][j]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (!is_valid_map_char(_map()->map[i][j + 1]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
	if (j == 0 || !is_valid_map_char(_map()->map[i][j - 1]))
	{
		print_map_unvalid_char(i, j);
		ft_exit("map not closed", 1);
	}
}

void	closed_map_check(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (_map()->map[i])
	{
		while (_map()->map[i][j])
		{
			if (_map()->map[i][j] == '0'
				|| is_start_position(_map()->map[i][j]))
				check_if_inside_map(i, j);
			j++;
		}
		j = 0;
		i++;
	}
}
