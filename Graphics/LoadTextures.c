/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:11:55 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 16:38:30 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	init_texture(t_tex **screen, char *path)
{
	*screen = mlx_load_png(path);
	if (*screen == NULL)
		error_hanlder(mlx_strerror(MLX_INVPNG));
}

static void	push_screen(t_screen **screen, t_coordinate pos, t_coordinate size)
{
	*screen = mlx_new_image(core()->mlx, size.x, size.y);
	if (*screen == NULL)
		error_hanlder(mlx_strerror(MLX_INVIMG));
	if (mlx_image_to_window(core()->mlx, *screen, pos.x, pos.y) == ERROR)
		error_hanlder(mlx_strerror(MLX_INVIMG));
}

void	init_screens(void)
{
	t_coordinate	size;

	size = (t_coordinate){WIN_WIDTH, WIN_HEIGHT};
	push_screen(&core()->screen, (t_coordinate){0, 0}, size);
	push_screen(&core()->front, (t_coordinate){0, 0}, size);
	size = (t_coordinate){MINIMAP, MINIMAP};
	push_screen(&core()->mini, (t_coordinate){15, 14}, size);
	push_screen(&core()->view, (t_coordinate){20, 19}, size);
	push_screen(&core()->player, (t_coordinate){15, 14}, size);
	size = (t_coordinate){size.x + 10, size.y + 10};
	push_screen(&core()->frame, (t_coordinate){10, 9}, size);
	size = (t_coordinate){size.x - 10, size.y - 10};
	push_screen(&core()->gloss, (t_coordinate){20, 19}, size);
}

void	load_textures(void)
{
	init_texture(&data()->images.east, data()->textures.east);
	init_texture(&data()->images.west, data()->textures.west);
	init_texture(&data()->images.south, data()->textures.south);
	init_texture(&data()->images.north, data()->textures.north);
	init_texture(&data()->images.player, "Textures/Minimap/ship.png");
	init_texture(&data()->images.frame, "Textures/Minimap/frame.png");
	init_texture(&data()->images.gloss, "Textures/Minimap/gloss.png");
	init_texture(&data()->images.view, "Textures/Minimap/view.png");
}
