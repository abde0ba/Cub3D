/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplyTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/15 10:51:46 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	color_floor_ceiling(int ray, int y)
{
	if (y < data()->wall.start)
		mlx_put_pixel(data()->game.screen, ray, y, data()->colors.floor);
	else if (y > data()->wall.end)
		mlx_put_pixel(data()->game.screen, ray, y, data()->colors.ceiling);
}

void	apply_texture_to_ray(t_ray *ray, t_wall *wall, int y_axis)
{
	uint32_t	p;
	uint32_t	color;
	uint8_t		*pixels;

	pixels = data()->images.north->pixels;
	p = data()->images.north->width * wall->offset_y + wall->offset_x;
	color = set_color(pixels[p], pixels[p + 1], pixels[p + 2], pixels[p + 3]);
	mlx_put_pixel(data()->game.screen, ray->index, y_axis, color);
}

void	render_walls(t_ray *ray, t_wall *wall)
{
	int		y_axis;

	y_axis = 0;
	wall->offset_x = (int)ray->hit_point % TILE;
	while (y_axis < WIN_HEIGHT)
	{
		wall->offset_y = y_axis - wall->start;
		wall->offset_y *= ((double)data()->images.north->height / wall->height);
		color_floor_ceiling(ray->index, y_axis);
		if (y_axis >= wall->start && y_axis <= wall->end)
			apply_texture_to_ray(ray, wall, y_axis);
		y_axis++;
	}
}
