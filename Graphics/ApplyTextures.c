/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplyTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/16 09:36:16 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_textures(t_ray *ray)
{
	core()->current = data()->images.south;
	if (ray->wall_horz.y > data()->player.pos.y)
		core()->current = data()->images.north;
	if (ray->is_vert && ray->wall_vert.x > data()->player.pos.x)
		core()->current = data()->images.east;
	else if (ray->is_vert && ray->wall_vert.x <= data()->player.pos.x)
		core()->current = data()->images.west;
}

void	color_floor_ceiling(int ray, int y)
{
	if (y < data()->wall.start)
		mlx_put_pixel(core()->screen, ray, y, data()->colors.floor);
	else if (y > data()->wall.end)
		mlx_put_pixel(core()->screen, ray, y, data()->colors.ceiling);
}

void	apply_texture_to_ray(t_wall *wall, int x_axis, int y_axis)
{
	uint32_t	p;
	uint32_t	color;
	uint8_t		*pixels;

	pixels = core()->current->pixels;
	wall->offset_y = y_axis - wall->start;
	wall->offset_y *= core()->current->height / wall->height;
	p = core()->current->width * wall->offset_y + wall->offset_x;
	p *= core()->current->bytes_per_pixel;
	color = set_color(pixels[p], pixels[p + 1], pixels[p + 2], pixels[p + 3]);
	mlx_put_pixel(core()->screen, x_axis, y_axis, color);
}

void	render_walls(t_ray *ray, t_wall *wall)
{
	int		y_axis;

	y_axis = 0;
	get_textures(ray);
	wall->offset_x = (int)(ray->hit_point * core()->current->width / TILE);
	wall->offset_x %= core()->current->width;
	while (y_axis < WIN_HEIGHT)
	{
		color_floor_ceiling(ray->index, y_axis);
		if (y_axis >= wall->start && y_axis <= wall->end)
			apply_texture_to_ray(wall, ray->index, y_axis);
		y_axis++;
	}
}
