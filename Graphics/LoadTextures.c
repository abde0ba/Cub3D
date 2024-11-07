/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:11:55 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/06 15:52:31 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static mlx_texture_t	*init_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		error_hanlder(mlx_strerror(MLX_INVPNG));
	return (texture);
}

void	get_textures(t_ray *ray)
{
	core()->current = data()->images.north;
	if (!ray->is_vert && ray->wall_horz.y > data()->player.pos.y)
	{
		ray->reverse = true;
		core()->current = data()->images.south;
	}
	else if (ray->is_vert && ray->wall_vert.x <= data()->player.pos.x)
	{
		ray->reverse = true;
		core()->current = data()->images.west;
	}
	else if (ray->is_vert && ray->wall_vert.x > data()->player.pos.x)
		core()->current = data()->images.east;
}

static void	init_screens(t_game *game)
{
	game->back = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->screen = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->zoom = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->mini_1 = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	game->mini_2 = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	game->mini_3 = mlx_new_image(game->mlx, MINIMAP + 10, MINIMAP + 10);
	game->mini_4 = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	game->mini_5 = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	if (game->screen == NULL || game->zoom == NULL || game->mini_1 == NULL
		|| game->mini_2 == NULL || game->mini_3 == NULL || game->mini_4 == NULL
		|| game->mini_5 == NULL || game->back == NULL)
		error_hanlder(mlx_strerror(MLX_INVIMG));
	mlx_image_to_window(game->mlx, game->back, 0, 0);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	mlx_image_to_window(game->mlx, game->zoom, 0, 0);
	mlx_image_to_window(game->mlx, game->mini_1, 15, 14);
	mlx_image_to_window(game->mlx, game->mini_4, 20, 19);
	mlx_image_to_window(game->mlx, game->mini_2, 15, 14);
	mlx_image_to_window(game->mlx, game->mini_3, 10, 9);
	mlx_image_to_window(game->mlx, game->mini_5, 20, 19);
}

void	load_textures(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (game->mlx == NULL)
		error_hanlder(mlx_strerror(MLX_WINFAIL));
	init_screens(game);
	data()->images.east = init_texture(data()->textures.east);
	data()->images.west = init_texture(data()->textures.west);
	data()->images.south = init_texture(data()->textures.south);
	data()->images.north = init_texture(data()->textures.north);
	data()->images.player = init_texture("Textures/ship.png");
	data()->images.frame = init_texture("Textures/frame.png");
	data()->images.gloss = init_texture("Textures/gloss.png");
	data()->images.view = init_texture("Textures/view.png");
	data()->images.back = init_texture("Textures/hole.png");
}
