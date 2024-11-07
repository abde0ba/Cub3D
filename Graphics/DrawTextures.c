/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:57:00 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/05 10:34:14 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	draw_texture(uint x, uint y, mlx_tex *texture, mlx_screen *screen)
{
	uint			color;
	uint			index;
	uint8_t			*pixels;
	t_coordinates	axis;

	axis.x = 0;
	pixels = texture->pixels;
	while (axis.x < texture->width)
	{
		axis.y = 0;
		while (axis.y < texture->height)
		{
			index = axis.y * texture->width + axis.x;
			index *= texture->bytes_per_pixel;
			color = set_color(pixels[index], pixels[index + 1],
				pixels[index + 2], pixels[index + 3]);
			mlx_put_pixel(screen, axis.x + x, axis.y + y, color);
			axis.y++;
		}
		axis.x++;
	}
}
