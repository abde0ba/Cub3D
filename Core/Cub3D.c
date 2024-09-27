/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/09/26 16:25:36 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_player_pos(t_cub3d *data)
{
	int x;
	int y;

	y = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'N')
				data->player.angle = (3 * M_PI) / 2;
			else if (data->map.grid[y][x] == 'S')
				data->player.angle = (M_PI) / 2;
			else if (data->map.grid[y][x] == 'E')
				data->player.angle = 2 * M_PI;
			else if (data->map.grid[y][x] == 'W')
				data->player.angle = M_PI;
			x++;
		}
			y++;			
	}
}

t_cub3d	*data(void)
{
	static short		set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.angle = ranging_angle(M_PI / 2);
		data.player.rot.speed = (M_PI / 180);
		data.player.walk.speed = TILE / 20;
		data.player.rot.direction = 0;
		data.player.walk.direction = 0;
		set = 1;
	}
	return (&data);
}

static mlx_image_t	*init_image(char *path)
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

int	main(int ac, char **av)
{
	data()->map.file = ac;
	data()->map.load = av[1];
	parser();
	data()->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data()->mlx)
		error_hanlder(YELLOW "<mlx>" RESET " Failed"); // PAUSE
	data()->images.screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data()->images.screen)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	data()->images.east = init_image(data()->textures.east);
	data()->images.west = init_image(data()->textures.west);
	data()->images.south = init_image(data()->textures.south);
	data()->images.north = init_image(data()->textures.north);
	get_player_pos(data());
	mlx_image_to_window(data()->mlx, data()->images.screen, 0, 0);
	mlx_loop_hook(data()->mlx, ft_hook, NULL);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (cleanup(), EXIT_SUCCESS);
}
