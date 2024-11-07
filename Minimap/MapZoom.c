/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapZoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:59 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/05 17:36:20 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cub3D.h"

void	refresh_display(mlx_screen *screen)
{
	t_coordinates	axis;

	axis.x = 0;
	while (axis.x < screen->width)
	{
		axis.y = 0;
		while (axis.y < screen->height)
		{
			mlx_put_pixel(screen, axis.x, axis.y, set_color(0, 0, 0, 0));
			axis.y++;
		}
		axis.x++;
	}
}

void	special_loop(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keydata.key == MLX_KEY_M)
		draw_texture(0, 0, data()->images.west, core()->zoom);
	refresh_display(core()->zoom);
}
