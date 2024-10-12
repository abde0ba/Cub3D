/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplyTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/12 18:42:01 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	color_floor_ceiling(int ray, int y, double wall_start, double wall_end)
{
	if (y < wall_start)
		mlx_put_pixel(data()->images.screen, ray, y, data()->colors.floor);
	else if (y > wall_end)
		mlx_put_pixel(data()->images.screen, ray, y, data()->colors.ceiling);
}

void	put_pixel(int ray, int y)
{
	uint32_t		p;
	uint8_t			*pixels;
	uint32_t		color;

	p = y * 4;
	pixels = data()->images.north->pixels;
	color = set_color(pixels[p], pixels[p + 1], pixels[p + 2], pixels[p + 3]);
	mlx_put_pixel(data()->images.screen, ray, y, color);
}

void	apply_texture_to_ray(int ray, int y, double mid_win, double mid_wall)
{
	color_floor_ceiling(ray, y, mid_win - mid_wall, mid_win + mid_wall);
	if (y >= mid_win - mid_wall && y <= mid_win + mid_wall)
		put_pixel(ray, y);
}

void	render_walls(int ray, double angle)
{
	int		y_axis;
	double	wall_height;
	double	angle_offset;
	double	ray_distance;

	y_axis = 0;
	angle_offset = cos(angle - data()->player.angle);
	ray_distance = data()->rays[ray].distance * angle_offset;
	wall_height = (TILE / ray_distance) * (WIN_WIDTH / 2) / tan(FOV / 2);
	while (y_axis < WIN_HEIGHT)
	{
		apply_texture_to_ray(ray, y_axis, WIN_HEIGHT / 2, wall_height / 2);
		y_axis++;
	}
}
