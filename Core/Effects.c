/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:35 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 03:45:14 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	put_pixel(t_screen *screen, t_crd axis, t_uint color)
{
	if (axis.x >= 0 && axis.x < screen->width
		&& axis.y >= 0 && axis.y < screen->height)
		mlx_put_pixel(screen, axis.x, axis.y, color);
}

void	game_effects(void)
{
	static	t_uint	frame;
	static	t_uint	reverse;

	if (frame == 26)
		reverse = 1;
	else if (frame == 0)
		reverse = 0;
	if (reverse == 0)
		frame++;
	else if (reverse && frame > 0)
		frame--;
	draw_texture(core()->front, data()->images.frames[frame], (t_crd){0, 0});
}
