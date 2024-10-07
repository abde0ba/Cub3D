/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ApplyTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:39 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 11:42:07 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	apply_textures(void)
{
	printf("[ %d ]\n", *data()->images.east->pixels);
}

static void draw_rect(double x, double y, double height)
{
	int	j;
	double	alpha;

	alpha = (200 / data()->rays[(int)x].distance) * 15;
	if (alpha > 255)
		alpha = 255;
	j = 0;
	while (j < height)
	{
		mlx_put_pixel(data()->images.screen, x, y + j, set_color(255, 255, 255, alpha));
		j++;
	}
}

void	render_walls(void)
{
	int		i;
	double	ray_distance;
	double	distance_proj_plane;
	double	wall_strip_height;

	i = 0;
	color_floor_ceiling();
	while (i < WIN_WIDTH)
	{
		ray_distance = data()->rays[i].distance * cos(data()->rays[i].angle - data()->player.angle);
		distance_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		wall_strip_height = (TILE / ray_distance) * distance_proj_plane;
		if (wall_strip_height > WIN_HEIGHT)
			wall_strip_height = WIN_HEIGHT;
		if (distance_proj_plane > WIN_WIDTH)
			distance_proj_plane = WIN_WIDTH;
		draw_rect(i, (WIN_HEIGHT / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
	apply_textures();
}
