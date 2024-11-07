/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapFrame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:26:28 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 18:26:11 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

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
