/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:57:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 14:59:00 by abadouab         ###   ########.fr       */
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

int	set_player_angle(char set)
{
	if (set == '0')
		return (false);
	data()->player.angle = M_PI;
	if (set == 'S')
		data()->player.angle /= 2;
	else if (set == 'N')
		data()->player.angle = 3 * M_PI / 2;
	else if (set == 'E')
		data()->player.angle *= 2;
	return (true);
}

int	check_player_in_wall(double y, double x, char dir)
{
	int	index_x;
	int	index_y;
	int	len_x;
	int	len_y;

	index_y = floor(y / TILE);
	index_x = floor(x / TILE);
	len_y = 0;
	while (data()->map.grid[len_y])
		len_y++;
	len_x = data()->map.width;
	if ((len_y > index_y) && (index_y > -1)
		&& (len_x > index_x) && (index_x > -1))
	{
		if (data()->map.grid[index_y][index_x] == '1')
			return (1);
		else if (data()->map.grid[index_y][index_x] == 'D')
		{
			if (check_if_door_open_close(y, x, dir))
				return (1);
			else if (!check_if_door_open_close(y, x, dir))
				return (0);
		}
	}
	return (0);
}

void	check_player_moving_l_and_r(double *x, double *y)
{
	double	check_y;
	double	check_x;

	if (data()->player.l_r.direction == 1)
	{
		check_y = data()->player.pos.y - sin(data()->player.angle + \
					(90 * M_PI / 180)) * 3.2;
		check_x = data()->player.pos.x - cos(data()->player.angle + \
					(90 * M_PI / 180)) * 3.2;
		if (!check_player_in_wall(check_y, check_x, '\0'))
			(1) && (*x = check_x, *y = check_y);
	}
	else if (data()->player.l_r.direction == -1)
	{
		check_y = data()->player.pos.y + sin(data()->player.angle + \
					(90 * M_PI / 180)) * 3.2;
		check_x = data()->player.pos.x + cos(data()->player.angle + \
					(90 * M_PI / 180)) * 3.2;
		if (!check_player_in_wall(check_y, check_x, '\0'))
			(1) && (*x = check_x, *y = check_y);
	}
}

void	move_player(void)
{
	double	x;
	double	y;
	double	step;

	data()->player.angle += data()->player.rot.direction * \
		data()->player.rot.speed;
	step = data()->player.walk.direction * data()->player.walk.speed;
	x = data()->player.pos.x + cos(data()->player.angle) * step;
	y = data()->player.pos.y + sin(data()->player.angle) * step;
	check_player_moving_l_and_r(&x, &y);
	if (data()->player.pos.x < x
		&& !check_player_in_wall(data()->player.pos.y, x + 10, '\0'))
		data()->player.pos.x = x;
	else if (data()->player.pos.x > x
		&& !check_player_in_wall(data()->player.pos.y, x - 10, '\0'))
		data()->player.pos.x = x;
	if (data()->player.pos.y < y
		&& !check_player_in_wall(y + 10, data()->player.pos.x, '\0'))
		data()->player.pos.y = y;
	else if (data()->player.pos.y > y
		&& !check_player_in_wall(y - 10, data()->player.pos.x, '\0'))
		data()->player.pos.y = y;
}
