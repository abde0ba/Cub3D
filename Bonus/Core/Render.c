/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 19:21:40 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

bool	move_detected(void)
{
	return (core()->mouse == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_RIGHT) == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_LEFT) == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_W) == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_S) == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_A) == true
		|| mlx_is_key_down(core()->mlx, MLX_KEY_D) == true);
}

void	render(void)
{
	move_player();
	doors_should_open_or_close();
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
	open_doors();
	if (mlx_is_key_down(core()->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core()->mlx);
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
	// if (move_detected() == true)
	render();
}
