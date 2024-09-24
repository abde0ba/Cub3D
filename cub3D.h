/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:17:19 by abbaraka          #+#    #+#             */
/*   Updated: 2024/09/24 18:02:35 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>


# define WIDTH 1280
# define HEIGHT 720
# define TILE 30
# define FOV (60 * (M_PI / 180))

typedef struct	s_ray
{
	int		col_i;
	double	angle;
	double	wall_horz_x;
	double	wall_horz_y;
	double	wall_vert_x;
	double	wall_vert_y;
	double	distance;
}				t_ray;

typedef struct	s_player
{
	double	x_pos;
	double	y_pos;
	double	angle;
	double	rot_speed;
	double	walk_speed;
	int		walk_dir;
	int		rot_dir;
}				t_player;

typedef	struct	s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		**map;
	t_player	*player;
	t_ray		*rays;
}		t_data;

//	**********  INIT_DATA  **********
void	init_player(t_data *data);
void	get_player_pos(t_data *data);
char	**put_map(char *arg);



#endif