/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 07:59:32 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	mouse_move(double x, double y, void *param)
{
	int32_t	offset_x;

	((void)param, (void)y);
	if (mlx_is_key_down(core()->mlx, MLX_KEY_F))
		return (mlx_set_cursor_mode(core()->mlx, MLX_MOUSE_NORMAL));
	mlx_set_cursor_mode(core()->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(core()->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	offset_x = x - (WIN_WIDTH / 2);
	data()->player.angle += offset_x * (data()->player.rot.speed / 4);
	core()->mouse = true;
}

int	main(int ac, char **av)
{
	data()->map.file = ac;
	data()->map.load = av[1];
	parser();
	core();
	render();
	mlx_loop_hook(core()->mlx, game_loop, NULL);
	mlx_cursor_hook(core()->mlx, mouse_move, NULL);
	mlx_loop(core()->mlx);
	mlx_terminate(core()->mlx);
	return (cleanup(), EXIT_SUCCESS);
}
