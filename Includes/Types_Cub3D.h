/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Types_Cub3D.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:33:41 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/14 22:29:48 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_CUB3D_H
# define TYPES_CUB3D_H

# include "MLX42.h"

typedef mlx_texture_t	t_tex;
typedef unsigned int	t_uint;
typedef mlx_image_t		t_screen;

// Struct For x And y Coordinates (uint)
typedef struct s_coordinate
{
	t_uint			x;				// X coordinate
	t_uint			y;				// Y coordinate
}					t_crd;

// Struct For x And y Coordinates (double)
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

// Struct for map data
typedef struct s_map
{
	bool			valid;			//	Check map is valid
	int				file;			// File Descriptor Map
	int				width;			// The Map width (line width)
	int				height;			// The Map height (rows)
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
	t_tex			*north;			// Texture for north wall
	t_tex			*south;			// Texture for south wall
	t_tex			*east;			// Texture for east wall
	t_tex			*west;			// Texture for west wall
	t_tex			*player;		// Texture for player
	t_tex			*frame;			// Texture for MiniMap
	t_tex			*gloss;			// Texture for MiniMap
	t_tex			*view;			// Texture for MiniMap
	t_tex			*frames[27];	// Texture for Player
}					t_image;

// Struct for floor and ceiling colors
typedef struct s_colors
{
	bool			setfloor;		// Floor color set
	bool			setceiling;		// Ceiling color set
	t_uint			floor;			// Floor color Value
	t_uint			ceiling;		// Ceiling color Value
}					t_colors;

// Struct for wall rendering information
typedef struct s_mini
{
	int				mid_w;			// Map texture Medium Width
	int				mid_h;			// Map texture Medium height
	double			acos;			// Player Angle cos
	double			asin;			// Player Angle sin
	t_uint			mid_m;			// Map Medium (height & Width)
	t_uint			color;			// Color Of The Current Pixel
	t_tex			*frame;			// Texture for MiniMap
}					t_mini;

// Struct for core game elements and rendering
typedef struct s_game
{
	bool			mouse;			// Set when the mouse position changes
	t_uint			mid_h;			// Screen medium height
	t_uint			mid_w;			// Screen medium with
	double			proj_depth;		// Distance to the projection plane
	mlx_t			*mlx;			// Pointer to Main MLX
	t_screen		*screen;		// Main image to draw pixels
	t_screen		*front;			// Screen to draw player
	t_screen		*mini;			// Minimap screen (first layer)
	t_screen		*player;		// Minimap screen (second layer)
	t_screen		*view;			// Minimap screen (third layer)
	t_screen		*frame;			// Minimap screen (fourth layer)
	t_screen		*gloss;			// Minimap screen (fifth layer)
	t_tex			*current;		// Texture (current direction)
}					t_game;

// Struct for ray information used in raycasting
typedef struct s_ray
{
	bool			reverse;		// X is reversed
	int				index;			// Index number of this ray
	double			angle;			// Angle of the ray
	double			distance;		// Distance to the closest wall
	double			hit_point;		// Point of impact on the wall
	double			is_vert;		// Point of impact on the wall
	t_coordinates	wall_horz;		// Intersection point (horizontal walls)
	t_coordinates	wall_vert;		// Intersection point (vertical walls)
}					t_ray;

// Struct for wall rendering information
typedef struct s_wall
{
	t_uint			offset_x;		// X texture offset
	t_uint			offset_y;		// Y texture offset
	double			end;			// Y-coordinate where the wall ends
	double			start;			// Y-coordinate where the wall starts
	double			height;			// Wall height in projection
	t_ray			*ray;			// Ray information (Current)
}					t_wall;

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
