/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 14:55:16 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>

# include "CLib.h"
# include "Types_bonus.h"

///////////////// CUB3D WINDOW /////////////////

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MINIMAP 200

///////////////// CUB3D MACROS /////////////////

# define ERROR -1
# define TILE 30
# define FOV 1.0471975511965976 // 60 degrees in radians

///////////////// CUB3D COLORS /////////////////

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

///////////////// CUB3D OBJECTS /////////////////

t_cub3d		*data(void);
t_game		*core(void);

///////////////// CUB3D PARSER /////////////////

void		parser(void);
void		parse_map(void);
int			parse_color(char *object);
bool		valid_player_symbols(char symbol);
bool		map_invalid_symbols(char *line);
char		*parse_texture(char *object);
bool		duplicated_elements(char set);

///////////////// CUB3D RAYCAST /////////////////

double		ranging_angle(double angle);
int			check_hit_ray_horz(t_ray *ray, t_coordinates next_on_wall,
				t_coordinates step);
int			check_hit_ray_vert(t_ray *ray, t_coordinates next_on_wall,
				t_coordinates step);
void		raycasting(void);
double		calc_dist(double fx, double fy, double sx, double sy);
int			check_player_in_wall(double y, double x, char dir);
int			check_ray_dir_down_up(double angle);
int			check_ray_dir_righ_left(double angle);

///////////////// CUB3D MOVEMENTS /////////////////

void		move_player(void);
bool		move_detected(void);
int			set_player_angle(char set);

///////////////// CUB3D RANDER /////////////////

void		init_screens(void);
void		load_textures(void);
void		minimap_rander(void);
void		game_loop(void *param);
void		render_walls(t_ray *ray, t_wall *wall);
void		get_textures(t_ray *ray);
void		game_effects(void);
void		render(void);

///////////////// CUB3D MINIMAP /////////////////

void		draw_texture(t_screen *screen, t_tex *texture, t_crd s);
void		adjust_frame_angle(t_mini *mini);
void		refresh_minimap_display(void);

///////////////// CUB3D TOOLS /////////////////

void		put_pixel(t_screen *screen, t_crd axis, t_uint color);
t_uint		set_color(t_uint red, t_uint green, t_uint blue, t_uint all);
void		error_hanlder(const char *message);

///////////////// DOOR FUNCTIONS /////////////////

void		get_doors(void);
void		open_doors(void);
void		check_is_door(t_ray *ray);
int			check_if_door(double y, double x);
int			check_the_specific_door(double y, double x, char dir);
void		doors_should_open_or_close(void);
int			check_if_door_open_close(double y, double x, char dir);

#endif
