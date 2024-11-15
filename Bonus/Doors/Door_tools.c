/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Door_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:54:58 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 15:04:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

void	check_is_door(t_ray *ray)
{
	t_crd			set;
	t_crd			axis;

	set = (t_crd){0, 0};
	if (ray->is_vert == true)
	{
		axis.x = ray->wall_vert.x / TILE;
		axis.y = ray->wall_vert.y / TILE;
		(data()->player.pos.x > ray->wall_vert.x) && (set.x = 1);
		if (data()->map.grid[axis.y][axis.x - set.x] == 'D')
			ray->is_door = true;
	}
	if (ray->is_vert == false)
	{
		axis.x = ray->wall_horz.x / TILE;
		axis.y = ray->wall_horz.y / TILE;
		(data()->player.pos.y > ray->wall_horz.y) && (set.y = 1);
		if (data()->map.grid[axis.y - set.y][axis.x] == 'D')
			ray->is_door = true;
	}
}
