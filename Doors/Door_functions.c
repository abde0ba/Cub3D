/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Door_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:29:45 by abbaraka          #+#    #+#             */
/*   Updated: 2024/10/24 16:40:18 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	check_if_door_open_close(double y, double x)
{
	if (data()->doors[check_the_specific_door(y, x)].is_opening
		&& ((int)y % TILE < data()->doors \
		[check_the_specific_door(y, x)].progress))
		return (0);
	else if (data()->doors[check_the_specific_door(y, x)].is_closing
		&& ((int)y % TILE > data()->doors \
		[check_the_specific_door(y, x)].progress))
		return (1);
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
