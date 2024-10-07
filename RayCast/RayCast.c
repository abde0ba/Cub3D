/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayCast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:15:35 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 12:12:04 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	cast_the_ray_horz(t_ray *ray)
{
	t_coordinates	inter;
	t_coordinates	next_on_wall;
	t_coordinates	step;

	inter.y = TILE * floor(data()->player.pos_y / TILE);
	if (check_ray_dir_down_up(ray->angle))
		inter.y += TILE;
	inter.x = data()->player.pos_x + \
		(inter.y - data()->player.pos_y) / tan(ray->angle);
	step.y = TILE;
	if (!check_ray_dir_down_up(ray->angle))
		step.y *= -1;
	step.x = step.y / tan(ray->angle);
	if (check_ray_dir_righ_left(ray->angle) && step.x < 0)
		step.x *= -1;
	if (!check_ray_dir_righ_left(ray->angle) && step.x > 0)
		step.x *= -1;
	next_on_wall.x = inter.x;
	next_on_wall.y = inter.y;
	if (check_hit_ray_horz(ray, next_on_wall, step))
		return (1);
	return (0);
}

int	cast_the_ray_vert(t_ray *ray)
{
	t_coordinates	inter;
	t_coordinates	next_on_wall;
	t_coordinates	step;

	inter.x = TILE * floor(data()->player.pos_x / TILE);
	if (check_ray_dir_righ_left(ray->angle))
		inter.x += TILE;
	inter.y = data()->player.pos_y + \
		(inter.x - data()->player.pos_x) * tan(ray->angle);
	step.x = TILE;
	if (!check_ray_dir_righ_left(ray->angle))
		step.x *= -1;
	step.y = step.x * tan(ray->angle);
	if (!check_ray_dir_down_up(ray->angle) && step.y > 0)
		step.y *= -1;
	if (check_ray_dir_down_up(ray->angle) && step.y < 0)
		step.y *= -1;
	next_on_wall.x = inter.x;
	next_on_wall.y = inter.y;
	if (check_hit_ray_vert(ray, next_on_wall, step))
		return (1);
	return (0);
}

void	cast_the_ray(int i)
{
	t_ray	ray;
	double	horz_touch;
	double	vert_touch;

	(1) && (ray = data()->rays[i], horz_touch = 0, vert_touch = 0);
	if (cast_the_ray_horz(&ray))
	{
		horz_touch = calc_dist(data()->player.pos_x, data()->player.pos_y, \
		ray.wall_horz_x, ray.wall_horz_y);
	}
	else
		horz_touch = MAXFLOAT;
	if (cast_the_ray_vert(&ray))
	{
		vert_touch = calc_dist(data()->player.pos_x, data()->player.pos_y, \
		ray.wall_vert_x, ray.wall_vert_y);
	}
	else
		vert_touch = MAXFLOAT;
	if (horz_touch > vert_touch)
		ray.distance = vert_touch;
	else
		ray.distance = horz_touch;
	data()->rays[i] = ray;
}

void	raycasting(void)
{
	int		i;
	double	angle;

	i = 0;
	angle = ranging_angle(data()->player.angle - (FOV / 2));
	data()->rays = malloc(WIN_WIDTH * sizeof(t_ray));
	while (i < WIN_WIDTH)
	{
		data()->rays[i].wall_horz_x = 0;
		data()->rays[i].wall_horz_y = 0;
		data()->rays[i].wall_vert_x = 0;
		data()->rays[i].wall_vert_y = 0;
		data()->rays[i].distance = 0;
		data()->rays[i].col_i = i;
		data()->rays[i].angle = ranging_angle(angle);
		cast_the_ray(i);
		angle += (FOV / (WIN_WIDTH));
		i++;
	}
}
