/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FloorAndCeiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 10:06:27 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	color_floor_ceiling(void)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		if (y < WIN_HEIGHT / 2)
			color = data()->colors.floor;
		else
			color = data()->colors.ceiling;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(data()->images.screen, x, y, color);
			x++;
		}
		y++;
	}
}
