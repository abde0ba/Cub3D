/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:16:12 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/16 09:39:06 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	draw_player(void)
{
	int		i;
	int		j;
	int		x;
	int		y;

	y = ((data()->player.pos.y / TILE) * 15) - 2;
	x = ((data()->player.pos.x / TILE) * 15) - 4;
	i = y;
	while (i < y + 5)
	{
		j = x;
		while (j < x + 5)
		{
			mlx_put_pixel(core()->screen, j, i, set_color(255, 255, 155, 255));
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < 10)
		mlx_put_pixel(core()->screen, x + cos(data()->player.angle) * i + 3,
			y + sin(data()->player.angle) * i + 2,
			set_color(255, 255, 155, 255));
}

static void	draw_pixel(char color, int x, int y)
{
	int			i;
	int			j;

	i = y * 15;
	while (i < (y * 15) + 14)
	{
		j = x * 15;
		while (j < (x * 15) + 14)
		{
			if (color == 'r')
				mlx_put_pixel(core()->screen, i, j, set_color(255, 255, 255, 255));
			else if (color == 'b')
				mlx_put_pixel(core()->screen, i, j, set_color(0, 0, 0, 100));
			else if (color == 'y')
				mlx_put_pixel(core()->screen, i, j, set_color(255, 255, 0, 255));
			j++;
		}
		i++;
	}
}

void	minimap_rander(void)
{
	int		x;
	int		y;

	x = 0;
	while (data()->map.grid[x])
	{
		y = 0;
		while (data()->map.grid[x][y])
		{
			if (data()->map.grid[x][y] == '1')
				draw_pixel('r', x, y);
			else if (data()->map.grid[x][y] != ' ')
				draw_pixel('b', x, y);
			y++;
		}
		x++;
	}
	draw_player();
}
