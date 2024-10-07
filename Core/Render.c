/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 11:41:43 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	render(void)
{
	move_player();
	raycasting();
	if (data()->images.screen)
		mlx_delete_image(data()->mlx, data()->images.screen);
	(data()->images).screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data()->images.screen == NULL)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	render_walls();
	minimap_rander();
	mlx_image_to_window(data()->mlx, data()->images.screen, 0, 0);
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
