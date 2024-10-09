/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayHit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/10/09 15:38:39 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	check_hit_ray_horz(t_ray *ray, t_coordinates next_on_wall,
						t_coordinates step)
{
	double	check_next_on_wally;
	int		rows;

	rows = 0;
	while (data()->map.grid[rows])
		rows++;
	while (next_on_wall.x >= 0 && next_on_wall.x < data()->map.longline * TILE
		&& next_on_wall.y >= 0 && next_on_wall.y < rows * TILE)
	{
		check_next_on_wally = next_on_wall.y;
		if (!check_ray_dir_down_up(ray->angle))
			check_next_on_wally--;
		if (check_player_in_wall(check_next_on_wally, next_on_wall.x))
			return (ray->wall_horz_x = next_on_wall.x,
				ray->wall_horz_y = next_on_wall.y, 1);
		else
			(1) && (next_on_wall.x += step.x, next_on_wall.y += step.y);
	}
	return (0);
}

int	check_hit_ray_vert(t_ray *ray, t_coordinates next_on_wall,
						t_coordinates step)
{
	double	check_next_on_wallx;
	int		rows;

	rows = 0;
	while (data()->map.grid[rows])
		rows++;
	while (next_on_wall.x >= 0 && next_on_wall.x < data()->map.longline * TILE
		&& next_on_wall.y >= 0 && next_on_wall.y < rows * TILE)
	{
		check_next_on_wallx = next_on_wall.x;
		if (!check_ray_dir_righ_left(ray->angle))
			check_next_on_wallx--;
		if (check_player_in_wall(next_on_wall.y, check_next_on_wallx))
			return (ray->wall_vert_x = next_on_wall.x,
				ray->wall_vert_y = next_on_wall.y, 1);
		else
			(1) && (next_on_wall.x += step.x, next_on_wall.y += step.y);
	}
	return (0);
}
