/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayCast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:15:35 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/15 11:17:02 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void remove_distortion(t_ray *ray, t_wall *wall, double horz_touch, double vert_touch)
{
	ray->distance = horz_touch;
	ray->hit_point = ray->wall_horz.x;
	data()->game.current = data()->images.south;
	if (ray->wall_horz.x > data()->player.pos.x)
		data()->game.current = data()->images.north;
	if (horz_touch > vert_touch)
	{
		data()->game.current = data()->images.east;
		if (ray->wall_vert.x > data()->player.pos.x)
			data()->game.current = data()->images.west;
		ray->distance = vert_touch;
		ray->hit_point = ray->wall_vert.x;
	}
	ray->distance *= cos(ray->angle - data()->player.angle);
	wall->height = TILE / ray->distance * data()->game.proj_depth;
	wall->start = (WIN_HEIGHT / 2) - (wall->height / 2);
	wall->end = (WIN_HEIGHT / 2) + (wall->height / 2);
}

static int	cast_the_ray_horz(t_ray *ray)
{
	t_coordinates	inter;
	t_coordinates	next_on_wall;
	t_coordinates	step;

	inter.y = TILE * floor(data()->player.pos.y / TILE);
	if (check_ray_dir_down_up(ray->angle))
		inter.y += TILE;
	inter.x = data()->player.pos.x + \
		(inter.y - data()->player.pos.y) / tan(ray->angle);
	step.y = TILE;
	if (!check_ray_dir_down_up(ray->angle))
		step.y *= -1;
	step.x = TILE / tan(ray->angle);
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

static int	cast_the_ray_vert(t_ray *ray)
{
	t_coordinates	inter;
	t_coordinates	next_on_wall;
	t_coordinates	step;

	inter.x = TILE * floor(data()->player.pos.x / TILE);
	if (check_ray_dir_righ_left(ray->angle))
		inter.x += TILE;
	inter.y = data()->player.pos.y + \
		(inter.x - data()->player.pos.x) * tan(ray->angle);
	step.x = TILE;
	if (!check_ray_dir_righ_left(ray->angle))
		step.x *= -1;
	step.y = TILE * tan(ray->angle);
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

static void	cast_the_ray(int index, t_ray *ray)
{
	double	horz_touch;
	double	vert_touch;

	ray->index = index;
	horz_touch = MAXFLOAT;
	vert_touch = MAXFLOAT;
	if (cast_the_ray_horz(ray))
	{
		horz_touch = calc_dist(data()->player.pos.x, data()->player.pos.y, \
		ray->wall_horz.x, ray->wall_horz.y);
	}
	if (cast_the_ray_vert(ray))
	{
		vert_touch = calc_dist(data()->player.pos.x, data()->player.pos.y, \
		ray->wall_vert.x, ray->wall_vert.y);
	}
	remove_distortion(ray, &data()->wall, horz_touch, vert_touch);
	render_walls(ray, &data()->wall);
}

void	raycasting(void)
{
	int		index;
	double	angle;

	index = 0;
	angle = ranging_angle(data()->player.angle - (FOV / 2));
	data()->rays = ft_calloc(WIN_WIDTH, sizeof(t_ray));
	while (index < WIN_WIDTH)
	{
		data()->rays[index].angle = ranging_angle(angle);
		cast_the_ray(index, &data()->rays[index]);
		angle += FOV / WIN_WIDTH;
		index++;
	}
	free(data()->rays);
}
