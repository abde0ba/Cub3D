/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/15 22:00:41 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	render(void)
{
	move_player();
	if (game()->screen)
		mlx_delete_image(data()->mlx, game()->screen);
	game()->screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (game()->screen == NULL)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	raycasting();
	minimap_rander();
	mlx_image_to_window(data()->mlx, game()->screen, 0, 0);
	data()->player.rot.direction = 0;
	data()->player.walk.direction = 0;
	data()->player.l_r.direction = 0;
}

int	check_if_door(double y, double x)
{
	int	y_check;
	int	x_check;

	y_check = floor(y / TILE);
	x_check = floor(x / TILE);
	if (data()->map.grid[y_check][x_check] == 'D')
		return (1);
	return (0);
}

int	check_the_specific_door(double y, double x)
{
	int	y_check;
	int	x_check;
	int	i;

	y_check = floor(y / TILE);
	x_check = floor(x / TILE);
	i = 0;
	while (i < data()->d_number)
	if (data()->doors[i].coords.x == x_check
	&& data()->doors[i].coords.y == y_check)
		return (i);
	return (-1);
}

void	game_loop(void *param)
{
	
	(void) param;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data()->mlx);
	if (mlx_is_key_down(data()->mlx, MLX_KEY_O))
	{
		if (data()->rays[WIN_WIDTH / 2].distance <= 20)
		{
			if (data()->rays[WIN_WIDTH / 2].is_vert == true)
			{
				if (check_if_door(data()->rays[WIN_WIDTH / 2].wall_vert.y,
					data()->rays[WIN_WIDTH / 2].wall_vert.x))
				{
					data()->doors[check_the_specific_door(data()->\
					rays[WIN_WIDTH / 2].wall_vert.y, data()->rays\
					[WIN_WIDTH / 2].wall_vert.x)].state = 0;
				}
			}
		}
	}
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
