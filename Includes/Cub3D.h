/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/24 16:45:38 by abbaraka         ###   ########.fr       */
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
# define MINIMAP 160

///////////////// CUB3D MACROS /////////////////

# define TILE 30
# define FOV 1.0471975511965976 // 60 degrees in radians

///////////////// CUB3D COLORS /////////////////

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

///////////////// CUB3D PARSER /////////////////

t_cub3d		*data(void);
t_game		*core(void);
void		error_hanlder(const char *message);
void		parser(void);
void		parse_map(void);
int			parse_color(char *object);
bool		valid_player_symbols(char symbol);
bool		map_invalid_symbols(char *line);
char		*parse_texture(char *object);
bool		duplicated_elements(char set);
int			set_player_angle(char set);

///////////////// CUB3D RAYCAST /////////////////

double		ranging_angle(double angle);
int			check_hit_ray_horz(t_ray *ray, t_coordinates next_on_wall,
				t_coordinates step);
int			check_hit_ray_vert(t_ray *ray, t_coordinates next_on_wall,
				t_coordinates step);
void		raycasting(void);
double		calc_dist(double fx, double fy, double sx, double sy);
int			check_player_in_wall(double y, double x);
int			check_ray_dir_down_up(double angle);
int			check_ray_dir_righ_left(double angle);

///////////////// CUB3D RENDER /////////////////

void		load_textures(void);
void		minimap_rander(void);
void		game_loop(void *param);
void		move_player(void);
void		render_walls(t_ray *ray, t_wall *wall);
void		move_player(void);
uint		set_color(uint red, uint green, uint blue, uint all);
void		get_textures(t_ray *ray);
void		draw_player(void);
uint32_t	set_color(uint32_t red, uint32_t green,
				uint32_t blue, uint32_t all);

///////////////// DOOR FUNCTIONS /////////////////

void		get_doors(void);
int			check_if_door(double y, double x);
int			check_the_specific_door(double y, double x);
void		open_doors(void);
void		doors_should_open_or_close(void);
int			check_if_door_open_close(double y, double x);

#endif
