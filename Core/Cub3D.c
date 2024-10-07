/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 11:44:37 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

t_cub3d	*data(void)
{
	static short		set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.rot.speed = (M_PI / 180);
		data.player.walk.speed = TILE / 20;
		data.player.rot.direction = 0;
		data.player.walk.direction = 0;
		set = 1;
	}
	return (&data);
}

mlx_image_t	*init_image(char *path)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	image = mlx_texture_to_image(data()->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	return (image);
}

void	mouse_move()
{
	int32_t		x;
	int32_t		y;
	int32_t		offset_x;

	mlx_get_mouse_pos(data()->mlx, &x, &y);
	offset_x = x - (WIN_WIDTH / 2);
	data()->player.angle += offset_x * data()->player.rot.speed;
	mlx_set_mouse_pos(data()->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

int	main(int ac, char **av)
{
	data()->map.file = ac;
	data()->map.load = av[1];
	parser();
	data()->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data()->mlx)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	data()->images.east = init_image(data()->textures.east);
	data()->images.west = init_image(data()->textures.west);
	data()->images.south = init_image(data()->textures.south);
	data()->images.north = init_image(data()->textures.north);
	mlx_loop_hook(data()->mlx, game_loop, NULL);
	mlx_cursor_hook(data()->mlx, mouse_move, NULL);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (cleanup(), EXIT_SUCCESS);
}
