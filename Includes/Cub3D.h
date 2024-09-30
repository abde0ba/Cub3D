/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/09/28 14:52:53 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <math.h>

# include "CLib.h"
# include "Types_Cub3D.h"

# define ERROR -1

///////////////// CUB3D WINDOW /////////////////

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

///////////////// CUB3D MACROS /////////////////

# define TILE 30
# define FOV (60 * (M_PI / 180))

///////////////// CUB3D COLORS /////////////////

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

///////////////// CUB3D PARSER /////////////////

t_cub3d	*data(void);
void	error_hanlder(char *message);
void	parser(void);
void	parse_map(void);
int		parse_color(char *object);
bool	valid_player_symbols(char symbol);
bool	map_invalid_symbols(char *line);
char	*parse_texture(char *object);
bool	duplicated_elements(char set);
int		set_player_angle(char set);

///////////////// CUB3D RAYCAST /////////////////

double	ranging_angle(double angle);
void	raycasting(void);
double	calc_dist(double fx, double fy, double sx, double sy);
int		check_player_in_wall(double y, double x);
int		check_ray_dir_down_up(double angle);
int		check_ray_dir_righ_left(double angle);

///////////////// CUB3D RANDER /////////////////

void	minimap_rander(void);
void	ft_hook(void *param);
void	move_player(void);
void	draw_player(void);
int		set_color(int red, int green, int blue, int all);
mlx_image_t	*init_image(char *path);

#endif
