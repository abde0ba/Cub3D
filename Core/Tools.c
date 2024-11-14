/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:35 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 19:58:39 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	put_pixel(t_screen *screen, t_crd axis, t_uint color)
{
	if (axis.x >= 0 && axis.x < screen->width
		&& axis.y >= 0 && axis.y < screen->height)
		mlx_put_pixel(screen, axis.x, axis.y, color);
}
