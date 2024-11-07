/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:16:12 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/05 16:14:43 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	render_mapped_pixel(t_mini *mini, t_coordinates axis)
{
	double			range;
	uint			color;

	color = set_color(200, 200, 200, 250);
	range = (axis.x - mini->mid_m) * (axis.x - mini->mid_m);
	range += (axis.y - mini->mid_m) * (axis.y - mini->mid_m);
	if (range < mini->mid_m * mini->mid_m && axis.x >= 0 && axis.y >= 0
		&& axis.x < MINIMAP  && axis.y < MINIMAP)
		mlx_put_pixel(core()->mini_1, axis.x, axis.y, color);
}

void	square_draw(t_mini *mini, t_coordinates start)
{
	t_coordinates	d;
	t_coordinates	axis;
	t_coordinates	offset;

	offset.y = 0.0;
	while (offset.y < 1.4)
	{
		offset.x = 0.0;
		while (offset.x < 1.4)
		{
			d.x = start.x + offset.x - mini->mid_m;
			d.y = start.y + offset.y - mini->mid_m;
			axis.x = (d.x * mini->acos) - (d.y * mini->asin) + mini->mid_m;
			axis.y = mini->mid_m - ((d.x * mini->asin) + (d.y * mini->acos));
			render_mapped_pixel(mini, axis);
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
	while (axis.y < 10)
	{
		axis.x = 0;
		while (axis.x < 10)
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
	t_mini			mini;

	refresh_minimap_display();
	mini.mid_m = MINIMAP / 2;
	mini.frame = data()->images.frame;
	mini.mid_w = mini.frame->width / 2;
	mini.mid_h = mini.frame->height / 2;
	mini.acos = cos(data()->player.angle);
	mini.asin = sin(data()->player.angle);
	move_depending(&mini);
	adjust_frame_angle(&mini);
}
