/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:21:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 15:54:53 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	close_screen(t_screen *screen)
{
	if (data()->map.valid && screen)
		mlx_delete_image(core()->mlx, screen);
}

static void	delete_texture(t_tex *texture)
{
	if (data()->map.valid && texture)
		mlx_delete_texture(texture);
}

static void	close_screens(void)
{
	close_screen(core()->screen);
	close_screen(core()->front);
	close_screen(core()->mini);
	close_screen(core()->player);
	close_screen(core()->view);
	close_screen(core()->frame);
	close_screen(core()->gloss);
}

static void	delete_textures(void)
{
	t_uint		frame;

	frame = 0;
	delete_texture(data()->images.east);
	delete_texture(data()->images.west);
	delete_texture(data()->images.south);
	delete_texture(data()->images.north);
	delete_texture(data()->images.player);
	delete_texture(data()->images.frame);
	delete_texture(data()->images.gloss);
	delete_texture(data()->images.view);
	while (frame < 27)
	{
		delete_texture(data()->images.frames[frame]);
		frame++;
	}
}

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
	close_screens();
	delete_textures();
	if (data()->map.valid && core()->mlx)
		mlx_terminate(core()->mlx);
	if (message == NULL)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
