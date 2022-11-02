/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:43 by mjallada          #+#    #+#             */
/*   Updated: 2022/11/02 13:24:35 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_print(char *error, int return_value)
{
	ft_printf_fd(2, "\033[1;31mError\033[0;39m\n> %s\n", error);
	return (return_value);
}

/* Used for key triggers that require a function that returns an int. */
int	exit_game(void)
{
	ft_exit(NULL, 0);
	exit(0);
}

/* Prints an error before freeing and exiting. */
void	ft_exit(char *error, int exit_code)
{
	if (error)
		error_print(error, 0);
	free_all();
	exit(exit_code);
}

/* Returns an int containing the RGB color values passed as parameter. */
int	color_generator(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
