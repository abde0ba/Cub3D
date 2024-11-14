/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapZoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:59 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/13 15:32:18 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cub3D.h"

void	refresh_display(t_screen *screen, t_uint color)
{
	t_coordinates	axis;

	axis.x = 0;
	while (axis.x < screen->width)
	{
		axis.y = 0;
		while (axis.y < screen->height)
		{
			mlx_put_pixel(screen, axis.x, axis.y, color);
			axis.y++;
		}
		axis.x++;
	}
}

static void	render_mapped_pixel(t_coordinates axis)
{
	t_uint			color;

	axis = (t_coordinates){axis.x *= 20, axis.y *= 20};
	color = set_color(255, 255, 255, 255);
	if (axis.x >= 0 && axis.x < WIN_WIDTH && axis.y >= 0 && axis.y < WIN_HEIGHT)
		mlx_put_pixel(core()->zoom, axis.x, axis.y, color);
}

static void	zoom_to_map(void)
{
	t_coordinates	index;
	t_coordinates	start;
	t_coordinates	axis;

	axis.y = 0;
	start.x = data()->player.pos.x - 420;
	start.y = data()->player.pos.y - 420;
	while (axis.y < 200)
	{
		axis.x = 0;
		while (axis.x < 200)
		{
			index.x = start.x / TILE + axis.x;
			index.y = start.y / TILE + axis.y;
			if(index.x >= 0 && index.x <= data()->map.width
				&& index.y >= 0 && index.y <= data()->map.height)
				{
					if (data()->map.grid[(int)index.y][(int)index.x] == '1')
						render_mapped_pixel((t_coordinates){axis.y, axis.x});
				}
			axis.x += 0.028;
		}
		axis.y += 0.028;
	}
}

void	special_loop(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keydata.key == MLX_KEY_M)
	{
		refresh_display(core()->zoom, set_color(0, 0, 0, 0));
		zoom_to_map();
	}
}
