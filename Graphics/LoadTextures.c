/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:11:55 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/22 17:28:37 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_textures(t_ray *ray)
{
	core()->current = data()->images.south;
	if (ray->wall_horz.y > data()->player.pos.y)
		core()->current = data()->images.north;
	if (ray->is_vert && ray->wall_vert.x > data()->player.pos.x)
		core()->current = data()->images.east;
	else if (ray->is_vert && ray->wall_vert.x <= data()->player.pos.x)
		core()->current = data()->images.west;
}

static mlx_texture_t	*init_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		error_hanlder(mlx_strerror(MLX_INVPNG));
	return (texture);
}

void	load_textures(void)
{
	data()->images.east = init_texture(data()->textures.east);
	data()->images.west = init_texture(data()->textures.west);
	data()->images.south = init_texture(data()->textures.south);
	data()->images.north = init_texture(data()->textures.north);
	data()->images.player = init_texture("Textures/player.png");
}
