/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:57:00 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 20:33:55 by abadouab         ###   ########.fr       */
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

void	draw_texture(t_screen *screen, t_tex *texture, t_crd s)
{
	t_crd			axis;
	t_uint			color;
	t_uint			index;
	uint8_t			*pixels;

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
			put_pixel(screen, (t_crd){s.x + axis.x, s.x + axis.y}, color);
			axis.y++;
		}
		axis.x++;
	}
}
