/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 03:42:48 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	render(void)
{
	move_player();
	raycasting();
	minimap_rander();
	data()->player.rot.direction = 0;
	data()->player.walk.direction = 0;
	data()->player.l_r.direction = 0;
	core()->mouse = false;
}

void	game_loop(void *param)
{
	(void) param;
	game_effects();
	if (mlx_is_key_down(core()->mlx, MLX_KEY_ESCAPE))
		error_hanlder(NULL);
	if (mlx_is_key_down(core()->mlx, MLX_KEY_W))
		data()->player.walk.direction = 1;
	if (mlx_is_key_down(core()->mlx, MLX_KEY_S))
		data()->player.walk.direction = -1;
	if (mlx_is_key_down(core()->mlx, MLX_KEY_LEFT))
		data()->player.rot.direction = -1;
	if (mlx_is_key_down(core()->mlx, MLX_KEY_RIGHT))
		data()->player.rot.direction = 1;
	if (mlx_is_key_down(core()->mlx, MLX_KEY_A))
		data()->player.l_r.direction = 1;
	if (mlx_is_key_down(core()->mlx, MLX_KEY_D))
		data()->player.l_r.direction = -1;
	if (move_detected() == true)
		render();
}
