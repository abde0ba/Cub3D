/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:35:49 by abbaraka          #+#    #+#             */
/*   Updated: 2024/11/04 17:33:30 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

void	count_and_allocate_doors(void)
{
	int		i;
	int		j;
	int		counter;

	(1) && (i = 0, counter = 0);
	while (data()->map.grid[i])
	{
		j = 0;
		while (data()->map.grid[i][j])
		{
			if (data()->map.grid[i][j] == 'D')
				counter++;
			j++;
		}
		i++;
	}
	data()->doors = allocate(counter, sizeof(t_door));
	data()->d_number = counter;
}

void	get_doors(void)
{
	int		i;
	int		j;
	int		index;

	count_and_allocate_doors();
	(1) && (i = 0, index = 0);
	while (data()->map.grid[i])
	{
		j = 0;
		while (data()->map.grid[i][j])
		{
			if (data()->map.grid[i][j] == 'D')
				(1) && (data()->doors[index].y = i,
				data()->doors[index].x = j,
				data()->doors[index].state = 0,
				data()->doors[index].progress = 0,
				data()->doors[index].closed = true, index++);
			j++;
		}
		i++;
	}
}

int	check_if_door(double y, double x)
{
	int	y_check;
	int	x_check;

	y_check = floor(y / TILE);
	x_check = floor(x / TILE);
	if (data()->map.grid[y_check][x_check] == 'D')
		return (1);
	return (0);
}

int	check_the_specific_door(double y, double x)
{
	int	y_check;
	int	x_check;
	int	i;

	y_check = floor(y / TILE);
	x_check = floor(x / TILE);
	i = 0;
	while (i < data()->d_number)
	{
		if (data()->doors[i].x == x_check && data()->doors[i].y == y_check)
			return (i);
		i++;
	}
	return (-1);
}

void	open_doors(void)
{
	int		i;
	float	distance;

	i = 0;
	while (i < data()->d_number)
	{
		distance = calc_dist(data()->doors[i].x * TILE + (TILE / 2),
				data()->doors[i].y * TILE + (TILE / 2),
				data()->player.pos.x, data()->player.pos.y);
		if (distance <= 30)
		{
			if (data()->doors[i].closed)
				(1) && (data()->doors[i].is_opening = true,
				data()->doors[i].is_closing = false);
		}
		else
		{
			if (data()->doors[i].opened)
				(1) && (data()->doors[i].is_closing = true,
				data()->doors[i].is_opening = false);
		}
		i++;
	}
}
