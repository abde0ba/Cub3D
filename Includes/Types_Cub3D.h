/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Types_Cub3D.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/07 13:50:38 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_CUB3D_H
# define TYPES_CUB3D_H

# include "MLX42.h"

// Struct For x And y Coordinates

typedef struct s_coordinates
{
	double	x;
	double	y;
}			t_coordinates;

// Struct for ray information
typedef struct s_ray
{
	double		angle;
	double		wall_horz_x;
	double		wall_horz_y;
	double		wall_vert_x;
	double		wall_vert_y;
	double		distance;
	int			col_i;
}				t_ray;

// Struct for player direction and moves
typedef struct s_move
{
	double			speed;		// Player's movement speed
	int				direction;	// Player's direction (angle)
}				t_move;

// Struct for player information
typedef struct s_player
{
	double			pos_x;			// Player's x-coordinate
	double			pos_y;			// Player's y-coordinate
	double			angle;			// Player's direction (angle)
	t_move			rot;			// Player's view direction
	t_move			walk;			// Player's walk direction move
	t_move			l_r;			// Player's left and right direction move
}					t_player;

// Struct for map data
typedef struct s_map
{
	char			*load;			// loading map file data
	char			**grid;			// 2D array for map grid
	short			file;			// File Descriptor Map
	int				longline;		// The Longest Map Line
}					t_map;

// Struct for textures
typedef struct s_textures
{
	void		*north;			// Texture for north wall
	void		*south;			// Texture for south wall
	void		*east;			// Texture for east wall
	void		*west;			// Texture for west wall
}				t_textures;

// Struct for Images
typedef struct s_image
{
	mlx_image_t	*screen;		// Main image to draw pixels
	mlx_image_t	*north;			// Image for north wall
	mlx_image_t	*south;			// Image for south wall
	mlx_image_t	*east;			// Image for east wall
	mlx_image_t	*west;			// Image for west wall
}				t_image;

// Struct for floor and ceiling colors
typedef struct s_colors
{
	int			floor;			// Floor color Value
	int			setfloor;		// Floor color set
	int			ceiling;		// Ceiling color Value
	int			setceiling;		// Ceiling color set
}					t_colors;

// Main Cub3D struct integrating all components
typedef struct s_cub3d
{
	mlx_t			*mlx;		// Pointer to Main MLX
	t_map			map;		// Map data
	t_textures		textures;	// Texture images
	t_image			images;		// Wall images
	t_colors		colors;		// Floor and ceiling colors
	t_player		player;		// Player information
	t_ray			*rays;		// Ray information
}					t_cub3d;

#endif
