/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:45 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/15 21:58:56 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

t_game	*game(void)
{
	static bool			set;
	static t_game		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_game));
		data.proj_depth = (WIN_WIDTH / 2) / tan(FOV / 2);
		set = 1;
	}
	return (&data);
}

t_cub3d	*data(void)
{
	static bool			set;
	static t_cub3d		data;

	if (set == 0)
	{
		ft_bzero(&data, sizeof(t_cub3d));
		data.player.rot.speed = (M_PI / 180);
		data.player.walk.speed = TILE / 20;
		set = 1;
	}
	return (&data);
}

void	count_and_allocate_doors()
{
	int		i;
	int		j;
	int		counter;
	
	(1) && (i = 0, counter = 0);
	while(data()->map.grid[i])
	{
		j = 0;
		while(data()->map.grid[i][j])
		{
			if (data()->map.grid[i][j] == 'D')
				counter++;
			j++;
		}
		i++;
	}
	data()->doors = allocate(counter, sizeof(t_door));
	data()->d_number = counter;
	// if (!doors)
	// 	(cleanup(), exit(1));
}

void	get_doors()
{
	int		i;
	int		j;
	int		index;

	count_and_allocate_doors();
	(1) && (i = 0, index = 0);
	while(data()->map.grid[i])
	{
		j = 0;
		while(data()->map.grid[i][j])
		{
			if (data()->map.grid[i][j] == 'D')
				(1) && (data()->doors[index].coords.y = i,
				data()->doors[index].coords.x = j,
				data()->doors[index].state = 1);
			j++;
		}
		i++;
	}
}

void	mouse_move(double a, double b, void *param)
{
	int32_t	x;
	int32_t	y;
	int32_t	offset_x;

	((void)param, (void)a, (void)b);
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
	get_doors();
	load_textures();
	mlx_loop_hook(data()->mlx, game_loop, NULL);
	mlx_cursor_hook(data()->mlx, mouse_move, NULL);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (cleanup(), EXIT_SUCCESS);
}
