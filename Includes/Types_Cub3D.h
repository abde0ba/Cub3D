/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Types_Cub3D.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/10/16 09:33:37 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_CUB3D_H
# define TYPES_CUB3D_H

# include "MLX42.h"

// Struct For x And y Coordinates
typedef struct s_coordinates
{
	double			x;				// X coordinate
	double			y;				// Y coordinate
}					t_coordinates;

// Struct for player direction and moves
typedef struct s_move
{
	int				direction;		// Player's direction (angle)
	double			speed;			// Player's movement speed
}					t_move;

// Struct for core game elements and rendering
typedef struct s_game
{
	mlx_t			*mlx;			// Pointer to Main MLX
	mlx_image_t		*screen;		// Main image to draw pixels
	mlx_texture_t	*current;		// Texture (current direction)
	double			proj_depth;		// Distance to the projection plane
}					t_game;

// Struct for wall rendering information
typedef struct s_wall
{
	uint32_t		offset_x;		// X texture offset
	uint32_t		offset_y;		// Y texture offset
	double			end;			// Y-coordinate where the wall ends
	double			start;			// Y-coordinate where the wall starts
	double			height;			// Wall height in projection
}					t_wall;

// Struct for map data
typedef struct s_map
{
	int				file;			// File Descriptor Map
	int				width;			// The Map width (line width)
	char			*load;			// loading map file data
	char			**grid;			// 2D array for map grid
}					t_map;

// Struct for player information
typedef struct s_player
{
	double			angle;			// Player's direction (angle)
	t_move			rot;			// Player's view direction
	t_move			walk;			// Player's walk direction move
	t_move			l_r;			// Player's left and right direction move
	t_coordinates	pos;			// Player's coordinates
}					t_player;

// Struct for textures (Path)
typedef struct s_textures
{
	void			*north;			// Path texture for north wall
	void			*south;			// Path texture for south wall
	void			*east;			// Path texture for east wall
	void			*west;			// Path texture for west wall
}					t_textures;

// Struct for Images (Textures)
typedef struct s_image
{
	mlx_texture_t	*north;			// Texture for north wall
	mlx_texture_t	*south;			// Texture for south wall
	mlx_texture_t	*east;			// Texture for east wall
	mlx_texture_t	*west;			// Texture for west wall
}					t_image;

// Struct for floor and ceiling colors
typedef struct s_colors
{
	bool			setfloor;		// Floor color set
	bool			setceiling;		// Ceiling color set
	uint32_t		floor;			// Floor color Value
	uint32_t		ceiling;		// Ceiling color Value
}					t_colors;

// Struct for ray information used in raycasting
typedef struct s_ray
{
	int				index;			// Index number of this ray
	double			angle;			// Angle of the ray
	double			distance;		// Distance to the closest wall
	double			hit_point;		// Point of impact on the wall
	double			is_vert;		// Point of impact on the wall
	t_coordinates	wall_horz;		// Intersection point (horizontal walls)
	t_coordinates	wall_vert;		// Intersection point (vertical walls)
}					t_ray;

// Main Cub3D struct integrating all components
typedef struct s_cub3d
{
	t_map			map;			// The map data and layout
	t_textures		textures;		// Texture images (Path)
	t_image			images;			// Laod images (Textures)
	t_colors		colors;			// Floor and ceiling colors
	t_player		player;			// Player information
	t_wall			wall;			// Wall rendering information
	t_ray			*rays;			// Ray information
}					t_cub3d;

#endif
