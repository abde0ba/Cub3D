/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:16:12 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 14:59:49 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

static void	render_mapped_pixel(t_mini *mini, t_coordinates axis)
{
	double			range;
	t_uint			color;

	color = set_color(200, 200, 200, 200);
	if (mini->is_door == true)
		color = set_color(200, 10, 10, 100);
	range = (axis.x - mini->mid_m) * (axis.x - mini->mid_m);
	range += (axis.y - mini->mid_m) * (axis.y - mini->mid_m);
	if (range < mini->mid_m * mini->mid_m)
		put_pixel(core()->mini, (t_crd){axis.x, axis.y}, color);
}

void	rotate_pixel(t_mini *mini, t_coordinates start)
{
	t_coordinates	d;
	t_coordinates	axis;
	double			offset;

	offset = 20.0;
	d.x = start.x * offset - mini->mid_m;
	d.y = start.y * offset - mini->mid_m;
	axis.x = (d.x * mini->acos) - (d.y * mini->asin) + mini->mid_m;
	axis.y = mini->mid_m - ((d.x * mini->asin) + (d.y * mini->acos));
	render_mapped_pixel(mini, axis);
}

void	move_depending(t_mini *mini)
{
	t_coordinates	index;
	t_coordinates	axis;

	axis.y = 0;
	while (axis.y < 10)
	{
		axis.x = 0;
		while (axis.x < 10)
		{
			mini->is_door = false;
			index.x = mini->start.x / TILE + axis.x;
			index.y = mini->start.y / TILE + axis.y;
			if (index.x >= 0 && index.x <= data()->map.width
				&& index.y >= 0 && index.y <= data()->map.height)
			{
				if (data()->map.grid[(int)index.y][(int)index.x] == 'D')
					mini->is_door = true;
				if (data()->map.grid[(int)index.y][(int)index.x] == '1'
					|| data()->map.grid[(int)index.y][(int)index.x] == 'D')
					rotate_pixel(mini, (t_coordinates){axis.y, axis.x});
			}
			axis.x += 0.034;
		}
		axis.y += 0.034;
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
	mini.start.x = data()->player.pos.x - 146;
	mini.start.y = data()->player.pos.y - 146;
	move_depending(&mini);
	adjust_frame_angle(&mini);
}