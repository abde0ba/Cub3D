/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:21:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 18:25:50 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

void	error_hanlder(const char *message)
{
	if (message)
	{
		ft_putstr_fd(RED"Error:\n"RESET, STDERR_FILENO);
		ft_putstr_fd("Cub3D: ", STDERR_FILENO);
		ft_putstr_fd((char *)message, STDERR_FILENO);
		ft_putstr_fd(RESET"\n", STDERR_FILENO);
	}
	cleanup();
	if (data()->map.file != ERROR)
		close(data()->map.file);
	if (core()->screen)
		mlx_delete_image(core()->mlx, core()->screen);
	if (core()->mlx)
		mlx_terminate(core()->mlx);
	exit(EXIT_FAILURE);
}
