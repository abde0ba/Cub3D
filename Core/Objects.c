/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/22 18:56:53 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

t_game	*core(void)
{
	static bool			set;
	static t_game		game;

	if (set == 0)
	{
		ft_bzero(&game, sizeof(t_game));
		game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
		if (game.mlx == NULL)
			error_hanlder(mlx_strerror(MLX_WINFAIL));
		game.screen = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
		game.s_mini = mlx_new_image(game.mlx, MINIMAP, MINIMAP);
		if (game.screen == NULL || game.s_mini == NULL)
			error_hanlder(mlx_strerror(MLX_INVIMG));
		mlx_image_to_window(game.mlx, game.screen, 0, 0);
		mlx_image_to_window(game.mlx, game.s_mini, 28, 28);
		game.proj_depth = (WIN_WIDTH / 2) / tan(FOV / 2);
		load_textures();
		set = 1;
	}
	return (&game);
}

t_cub3d	*data(void)
{
	static bool			set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.rot.speed = (double)M_PI / 180;
		data.player.walk.speed = (double)TILE / 12;
		set = 1;
	}
	return (&data);
}
