/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 16:57:39 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

// static void	game_effects(void)
// {
// 	static	t_uint	frame;
// 	static	t_uint	reverse;

// 	if (frame == 26)
// 		reverse = 1;
// 	else if (frame == 0)
// 		reverse = 0;
// 	if (reverse == 0)
// 		frame++;
// 	else if (reverse && frame > 0)
// 		frame--;
// 	draw_texture(0, 0, data()->images.frames[frame], core()->front);
// }

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
	// game_effects();
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
	if (move_detected() == true)
		render();
}
