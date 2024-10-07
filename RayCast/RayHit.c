/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayHit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/10/07 12:06:39 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	check_hit_ray_horz(t_ray *ray, t_coordinates next_on_wall,
						t_coordinates step)
{
	double	check_next_on_wally;

	while (next_on_wall.x >= 0 && next_on_wall.x < WIN_WIDTH
		&& next_on_wall.y >= 0 && next_on_wall.y < WIN_HEIGHT)
	{
		check_next_on_wally = next_on_wall.y;
		if (!check_ray_dir_down_up(ray->angle))
			check_next_on_wally--;
		if (check_player_in_wall(check_next_on_wally, next_on_wall.x))
		{
			ray->wall_horz_x = next_on_wall.x;
			ray->wall_horz_y = next_on_wall.y;
			return (1);
		}
		else
		{
			next_on_wall.x += step.x;
			next_on_wall.y += step.y;
		}
	}
	return (0);
}

int	check_hit_ray_vert(t_ray *ray, t_coordinates next_on_wall,
						t_coordinates step)
{
	double	check_next_on_wallx;

	while (next_on_wall.x >= 0 && next_on_wall.x < WIN_WIDTH
		&& next_on_wall.y >= 0 && next_on_wall.y < WIN_HEIGHT)
	{
		check_next_on_wallx = next_on_wall.x;
		if (!check_ray_dir_righ_left(ray->angle))
			check_next_on_wallx--;
		if (check_player_in_wall(next_on_wall.y, check_next_on_wallx))
		{
			ray->wall_vert_x = next_on_wall.x;
			ray->wall_vert_y = next_on_wall.y;
			return (1);
		}
		else
		{
			next_on_wall.x += step.x;
			next_on_wall.y += step.y;
		}
	}
	return (0);
}
