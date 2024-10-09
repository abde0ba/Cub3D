/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/09 16:02:00 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	draw_image(uint32_t x_axis, uint32_t y_axis)
{
	uint32_t	i;
	uint32_t	x;
	uint32_t	y;
	uint8_t		*pixels;
	uint32_t	color;

	(data()->images).screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	i = 0;
	x = x_axis;
	pixels = data()->images.south->pixels;
	while (x - x_axis < data()->images.south->width && x < WIN_WIDTH)
	{
		y = y_axis;
		if (y >= WIN_HEIGHT)
			i += data()->images.south->bytes_per_pixel;
		while (y - y_axis < data()->images.south->height && y < WIN_HEIGHT)
		{
			printf("X: [ %d ] Y: [ %d ]\n", x, y);
			color = set_color(pixels[i], pixels[i + 1],
				pixels[i + 2], pixels[i + 3]);
			mlx_put_pixel(data()->images.screen, y, x, color);
			i += data()->images.south->bytes_per_pixel;
			y++;
		}
		x++;
	}
	mlx_image_to_window(data()->mlx, data()->images.screen, 0, 0);
}

static void	render(void)
{
	raycasting();
	move_player();
	// if (data()->images.screen)
	// 	mlx_delete_image(data()->mlx, data()->images.screen);
	// (data()->images).screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	// if (data()->images.screen == NULL)
	// 	error_hanlder(YELLOW "<mlx>" RESET " Failed");
	// render_walls();
	// minimap_rander();
	// mlx_image_to_window(data()->mlx, data()->images.screen, 0, 0);
	data()->player.rot.direction = 0;
	data()->player.walk.direction = 0;
	data()->player.l_r.direction = 0;
	free(data()->rays);
}

void	game_loop(void *param)
{
	(void) param;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data()->mlx);
	if (mlx_is_key_down(data()->mlx, MLX_KEY_W))
		data()->player.walk.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_S))
		data()->player.walk.direction = -1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_LEFT))
		data()->player.rot.direction = -1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_RIGHT))
		data()->player.rot.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_A))
		data()->player.l_r.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_D))
		data()->player.l_r.direction = -1;
	render();
}
