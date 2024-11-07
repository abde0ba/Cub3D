/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 18:25:28 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

t_cub3d	*data(void)
{
	static bool			set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.rot.speed = (double)M_PI / 90;
		data.player.walk.speed = (double)TILE / 12;
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
		game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
		if (game.mlx == NULL)
			error_hanlder(mlx_strerror(MLX_WINFAIL));
		game.screen = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
		game.mini_1 = mlx_new_image(game.mlx, MINIMAP, MINIMAP);
		game.mini_2 = mlx_new_image(game.mlx, MINIMAP, MINIMAP);
		game.mini_3 = mlx_new_image(game.mlx, MINIMAP, MINIMAP);
		if (game.screen == NULL || game.mini_1 == NULL
			|| game.mini_2 == NULL || game.mini_3 == NULL)
			error_hanlder(mlx_strerror(MLX_INVIMG));
		mlx_image_to_window(game.mlx, game.screen, 0, 0);
		mlx_image_to_window(game.mlx, game.mini_1, 15, 14);
		mlx_image_to_window(game.mlx, game.mini_2, 15, 14);
		mlx_image_to_window(game.mlx, game.mini_3, 15, 14);
		game.proj_depth = (WIN_WIDTH / 2) / tan(FOV / 2);
		load_textures();
		set = 1;
	}
	return (&game);
}
