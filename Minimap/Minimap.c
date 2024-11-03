/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:16:12 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 12:42:41 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	draw_circle(double x, double y, double radius, int color)
{
	double		i;
	double		j;

	i = -radius;
	while (i < radius)
	{
		j = -radius;
		while (j < radius)
		{
			// if ((i * i) + (j * j) < (radius * radius))
				mlx_put_pixel(core()->mini_2, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	square_draw(t_mini *mini, t_coordinates start)
{
	t_coordinates	axis;
	t_coordinates	offset;
	uint			color;

	offset.y = 0.0;
	color = set_color(255, 255, 255, 255);
	while (offset.y < 2)
	{
		offset.x = 0.0;
		while (offset.x < 2)
		{
			axis.x = (start.x + offset.x - mini->mid_m) * mini->acos;
			axis.x -= (start.y + offset.y - mini->mid_m) * mini->asin;
			axis.x += mini->mid_m;
			axis.y = (start.x + offset.x - mini->mid_m) * mini->asin;
			axis.y += (start.y + offset.y - mini->mid_m) * mini->acos;
			axis.y += mini->mid_m;
			if (axis.x >= 0 && axis.x < MINIMAP
				&& axis.y >= 0 && axis.y < MINIMAP)
				mlx_put_pixel(core()->mini_2, axis.x, axis.y, color);
			offset.x += 0.68;
		}
		offset.y += 0.68;
	}
}

void	move_depending(t_mini *mini)
{
	t_coordinates	index;
	t_coordinates	start;
	t_coordinates	axis;

	axis.y = 0;
	start.x = data()->player.pos.x - 120;
	start.y = data()->player.pos.y - 120;
	while (axis.y < 8)
	{
		axis.x = 0;
		while (axis.x < 8)
		{
			index.x = start.x / TILE + axis.x;
			index.y = start.y / TILE + axis.y;
			if(index.x >= 0 && index.x <= data()->map.width
				&& index.y >= 0 && index.y <= data()->map.height)
				{
					mini->axis = (t_coordinates){axis.y * 25.0, axis.x * 25.0};
					if (data()->map.grid[(int)index.y][(int)index.x] == '1')
						square_draw(mini, mini->axis);
				}
			axis.x += 0.08;
		}
		axis.y += 0.08;
	}
}

void	minimap_rander(void)
{
	t_mini		mini;

	mini.mid_m = MINIMAP / 2;
	mini.frame = data()->images.frame;
	mini.mid_w = mini.frame->width / 2;
	mini.mid_h = mini.frame->height / 2;
	mini.acos = cos(data()->player.angle);
	mini.asin = sin(data()->player.angle);
	draw_circle(100, 100, 100, 0XF4D03F);
	draw_circle(100, 100, 5, set_color(0, 0, 0, 255));
	move_depending(&mini);
	adjust_frame_angle(&mini);
}
