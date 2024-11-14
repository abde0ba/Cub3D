/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:21:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/12 17:48:39 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

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
	exit(EXIT_FAILURE);
	if (data()->map.valid && core()->screen)
		mlx_delete_image(core()->mlx, core()->screen);
	if (data()->map.valid && core()->mlx)
		mlx_terminate(core()->mlx);
}
