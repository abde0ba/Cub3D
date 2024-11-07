/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplyTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/04 17:22:28 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

static void	color_floor_ceiling(int ray, int y)
{
	if (y < data()->wall.start)
		mlx_put_pixel(core()->screen, ray, y, data()->colors.floor);
	else if (y > data()->wall.end)
		mlx_put_pixel(core()->screen, ray, y, data()->colors.ceiling);
}

static uint	apply_shade_effects(uint8_t *pixels, double distance)
{
	uint		shade_r;
	uint		shade_g;
	uint		shade_b;
	double		intensity;

	intensity = 1.0 - (distance / 750.0);
	if (intensity < 0.4)
		intensity = 0.4;
	shade_r = (uint)(*pixels * intensity);
	shade_g = (uint)(*(pixels + 1) * intensity);
	shade_b = (uint)(*(pixels + 2) * intensity);
	return(set_color(shade_r, shade_g, shade_b, *(pixels + 3)));
}

static void	apply_texture_to_ray(t_wall *wall, int x_axis, int y_axis)
{
	uint		index;
	uint		color;
	uint8_t		*pixels;

	pixels = core()->current->pixels;
	wall->offset_y = y_axis - wall->start;
	wall->offset_y *= core()->current->height / wall->height;
	wall->offset_y %= core()->current->height;
	index = core()->current->width * wall->offset_y + wall->offset_x;
	index *= core()->current->bytes_per_pixel;
	color = apply_shade_effects(pixels + index, wall->ray->distance);
	mlx_put_pixel(core()->screen, x_axis, y_axis, color);
}

void	render_walls(t_ray *ray, t_wall *wall)
{
	int		y_axis;

	y_axis = 0;
	get_textures(ray);
	wall->offset_x = ray->hit_point * core()->current->width / TILE;
	wall->offset_x %= core()->current->width;
	while (y_axis < WIN_HEIGHT)
	{
		color_floor_ceiling(ray->index, y_axis);
		if (y_axis >= wall->start && y_axis <= wall->end)
			apply_texture_to_ray(wall, ray->index, y_axis);
		y_axis++;
	}
}
