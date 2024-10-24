/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:11:55 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/16 10:27:07 by abadouab         ###   ########.fr       */
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

void	load_textures(void)
{
	data()->images.east = init_texture(data()->textures.east);
	data()->images.west = init_texture(data()->textures.west);
	data()->images.south = init_texture(data()->textures.south);
	data()->images.north = init_texture(data()->textures.north);
}
