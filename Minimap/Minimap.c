/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:16:12 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/23 15:20:22 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

// void	push_image_to_window(char *path, int x_axis, int y_axis)
// {
// 	mlx_image_t		*image;
// 	mlx_texture_t	*texture;

// 	texture = mlx_load_png(path);
// 	if (texture == NULL)
// 		;
// 	image = mlx_texture_to_image(core()->mlx, texture);
// 	mlx_delete_texture(texture);
// 	if (image == NULL)
// 		;
// 	mlx_image_to_window(core()->mlx, image, x_axis, y_axis);
// 	mlx_delete_image(core()->mlx, image);
// }

void	minimap_rander(void)
{
	int		x_axis;
	int		y_axis;

	x_axis = 0;
	while (x_axis < MINIMAP)
	{
		y_axis = 0;
		while (y_axis < MINIMAP)
		{
			mlx_put_pixel(core()->s_mini, x_axis, y_axis, set_color(255, 255, 255, 40));
			y_axis++;
		}
		x_axis++;
	}
}
