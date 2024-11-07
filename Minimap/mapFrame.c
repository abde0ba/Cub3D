/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapFrame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:26:28 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/05 17:02:54 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	refresh_minimap_display(void)
{
	t_coordinates	axis;
	t_coordinates	start;
	double			radius;

	radius = MINIMAP / 2;
	start = (t_coordinates){radius, radius};
	axis.x = -radius;
	while (axis.x < radius)
	{
		axis.y = -radius;
		while (axis.y < radius)
		{
			if ((axis.x * axis.x) + (axis.y * axis.y) < (radius * radius))
				mlx_put_pixel(core()->mini_1, start.x + axis.x,
					start.y + axis.y, set_color(10, 10, 10, 80));
			axis.y++;
		}
		axis.x++;
	}
	draw_texture(80, 80, data()->images.player, core()->mini_2);
	draw_texture(0, 0, data()->images.view, core()->mini_4);
	draw_texture(0, 0, data()->images.gloss, core()->mini_5);
}

static void	render_mapped_pixel(t_mini *mini, uint index, t_coordinates offset)
{
	uint			pixel_r;
	uint			pixel_g;
	uint			pixel_b;
	uint			pixel_a;

	if (offset.x < 0 || offset.x >= mini->frame->width
		|| offset.y < 0 || offset.y >= mini->frame->height)
		return ;
	index *= mini->frame->bytes_per_pixel;
	pixel_r = mini->frame->pixels[index];
	pixel_g = mini->frame->pixels[index + 1];
	pixel_b = mini->frame->pixels[index + 2];
	pixel_a = mini->frame->pixels[index + 3];
	mini->color = set_color(pixel_r, pixel_g, pixel_b, pixel_a);
	mlx_put_pixel(core()->mini_3, offset.x, offset.y, mini->color);
}

void	adjust_frame_angle(t_mini *mini)
{
	uint			index;
	t_coordinates	d;
	t_coordinates	axis;
	t_coordinates	offset;

	axis.x = 0;
	while (axis.x < mini->frame->width)
	{
		axis.y = 0;
		while (axis.y < mini->frame->height)
		{
			d.x = axis.x - mini->mid_w;
			d.y = axis.y - mini->mid_h;
			offset.x = (d.x * mini->acos) - (d.y * mini->asin) + mini->mid_w;
			offset.y = (d.x * mini->asin) + (d.y * mini->acos) + mini->mid_h;
			index = axis.y * mini->frame->width + axis.x;
			render_mapped_pixel(mini, index, offset);
			axis.y++;
		}
		axis.x++;
	}
}
