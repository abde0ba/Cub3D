/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Door_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:29:45 by abbaraka          #+#    #+#             */
/*   Updated: 2024/11/03 19:02:15 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

int	set_horz_or_vert_door(double y, double x, double set)
{
	if (data()->doors[check_the_specific_door(y, x)].is_opening
		&& (int)set % TILE < data()->doors \
		[check_the_specific_door(y, x)].progress)
		return (0);
	else if (data()->doors[check_the_specific_door(y, x)].is_closing
		&& (int)set % TILE > data()->doors \
		[check_the_specific_door(y, x)].progress)
		return (1);
	return (-1);
}

int	check_if_door_open_close(double y, double x, char dir)
{
	if (dir == 'v')
	{
		if (set_horz_or_vert_door(y, x, y) == 1)
			return (1);
		else if (!set_horz_or_vert_door(y, x, y))
			return (0);
	}
	else if (dir == 'h')
	{
		if (set_horz_or_vert_door(y, x, x) == 1)
			return (1);
		else if (!set_horz_or_vert_door(y, x, x))
			return (0);
	}
	if (data()->doors[check_the_specific_door(y, x)].closed)
		return (1);
	else if (data()->doors[check_the_specific_door(y, x)].opened)
		return (0);
	return (-1);
}

void	increment_progress_in_opening(int i)
{
	if (data()->doors[i].is_opening)
	{
		if (data()->doors[i].progress < TILE)
			data()->doors[i].progress += 1;
		if (data()->doors[i].progress >= TILE)
		{
			data()->doors[i].progress = TILE;
			data()->doors[i].opened = true;
			data()->doors[i].closed = false;
			data()->doors[i].is_opening = false;
		}
	}
}

void	decrement_progress_in_closing(int i)
{
	if (data()->doors[i].is_closing)
	{
		if (data()->doors[i].progress > 0)
			data()->doors[i].progress -= 1;
		if (data()->doors[i].progress <= 0)
		{
			data()->doors[i].progress = 0;
			data()->doors[i].closed = true;
			data()->doors[i].opened = false;
			data()->doors[i].is_closing = false;
		}
	}
}

void	doors_should_open_or_close(void)
{
	int	i;

	i = 0;
	while (i < data()->d_number)
	{
		increment_progress_in_opening(i);
		decrement_progress_in_closing(i);
		i++;
	}
}