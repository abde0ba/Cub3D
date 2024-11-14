/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:57:00 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 17:03:19 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_textures(t_ray *ray)
{
	core()->current = data()->images.north;
	if (!ray->is_vert && ray->wall_horz.y > data()->player.pos.y)
	{
		ray->reverse = true;
		core()->current = data()->images.south;
	}
	else if (ray->is_vert && ray->wall_vert.x <= data()->player.pos.x)
	{
		ray->reverse = true;
		core()->current = data()->images.west;
	}
	else if (ray->is_vert && ray->wall_vert.x > data()->player.pos.x)
		core()->current = data()->images.east;
}

void	draw_texture(t_uint x, t_uint y, t_tex *texture, t_screen *screen)
{
	t_uint			color;
	t_uint			index;
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
