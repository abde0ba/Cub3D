/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 08:20:26 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

t_cub3d	*data(void)
{
	static bool			set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.rot.speed = (double)M_PI / 60;
		data.player.walk.speed = (double)TILE / 6;
		set = 1;
	}
	return (&data);
}

t_game	*core(void)
{
	static bool			set;
	static t_game		game;

	if (set == 0)
	{
		ft_bzero(&game, sizeof(t_game));
		game.proj_depth = (WIN_WIDTH / 2) / tan(FOV / 2);
		game.mid_h = WIN_HEIGHT / 2;
		game.mid_w = WIN_WIDTH / 2;
		set = 1;
	}
	return (&game);
}
