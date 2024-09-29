/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/09/28 19:01:51 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void draw_rect(double x, double y, double height)
{
	int	j;
	double	alpha;

	alpha = (200 / data()->rays[(int)x].distance) * 15;
	if (alpha > 255)
		alpha = 255;
	j = 0;
	while (j < height)
	{
		mlx_put_pixel(data()->images.screen, x, y + j, set_color(255, 255, 255, alpha));
		j++;
	}
}

static void	render_walls(void)
{
	int		i;
	double	ray_distance;
	double	distance_proj_plane;
	double	wall_strip_height;

	i = 0;
	while (i < WIN_WIDTH)
	{
		ray_distance = data()->rays[i].distance * cos(data()->rays[i].angle - data()->player.angle);
		distance_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		wall_strip_height = (TILE / ray_distance) * distance_proj_plane;
		if (wall_strip_height > WIN_HEIGHT)
			wall_strip_height = WIN_HEIGHT;
		if (distance_proj_plane > WIN_WIDTH)
			distance_proj_plane = WIN_WIDTH;
		draw_rect(i, (WIN_HEIGHT / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

static void	render(void)
{
	move_player();
	raycasting();
	if (data()->images.screen)
		mlx_delete_image(data()->mlx, data()->images.screen);
	data()->images.screen = mlx_new_image(data()->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data()->images.screen == NULL)
		error_hanlder(YELLOW "<mlx>" RESET " Failed");
	render_walls();
	minimap_rander();
	mlx_image_to_window(data()->mlx, data()->images.screen, 0, 0);
	data()->player.rot.direction = 0;
	data()->player.walk.direction = 0;
	data()->player.l_r.direction = 0;
	free(data()->rays);
}

void ft_hook(void *param)
{
	(void) param;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data()->mlx);
	if (mlx_is_key_down(data()->mlx, MLX_KEY_W))
		data()->player.walk.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_S))
		data()->player.walk.direction = -1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_LEFT))
		data()->player.rot.direction = -1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_RIGHT))
		data()->player.rot.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_A))
		data()->player.l_r.direction = 1;
	if (mlx_is_key_down(data()->mlx, MLX_KEY_D))
		data()->player.l_r.direction = -1;
	render();
}
