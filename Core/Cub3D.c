/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 15:55:49 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	mlx_start(void)
{
	core();
	core()->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (core()->mlx == NULL)
		error_hanlder(mlx_strerror(MLX_WINFAIL));
	init_screens();
	load_textures();
	render();
}

void	mouse_move(double x, double y, void *param)
{
	int32_t	offset_x;

	core()->mouse = true;
	((void)param, (void)y);
	if (mlx_is_key_down(core()->mlx, MLX_KEY_F))
		return (mlx_set_cursor_mode(core()->mlx, MLX_MOUSE_NORMAL));
	mlx_set_cursor_mode(core()->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(core()->mlx, core()->mid_w, core()->mid_h);
	offset_x = x - core()->mid_w;
	data()->player.angle += offset_x * (data()->player.rot.speed / 5.2);
}

int	main(int ac, char **av)
{
	data()->map.file = ac;
	data()->map.load = av[1];
	parser();
	mlx_start();
	mlx_loop_hook(core()->mlx, game_loop, NULL);
	mlx_cursor_hook(core()->mlx, mouse_move, NULL);
	mlx_loop(core()->mlx);
	error_hanlder(NULL);
}
