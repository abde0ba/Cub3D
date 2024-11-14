#include "Cub3D.h"

void	draw_line(t_coordinates start, double length, t_uint color)
{
	double			distance;
	t_coordinates	axis;

	distance = 0.0;
	axis = (t_coordinates){0, 0};
	while (distance < length)
	{
		axis.x = start.x + (distance * cos(data()->player.angle));
		axis.y = start.y + (distance * sin(data()->player.angle));
		mlx_put_pixel(core()->player, axis.x, axis.y, color);
		distance++;
	}
}

void	draw_square(t_coordinates start)
{
	t_uint			color;
	int				side;
	double			angle;
	double			distance;
	t_coordinates	axis;

	side = 0;
	color = set_color(255, 255, 255, 100);
	while (side < 4)
	{
		distance = 0.0;
		angle = data()->player.angle + (M_PI / 2) * side;
		while (distance < 20.0)
		{
			axis.x = start.x + (distance * cos(angle));
			axis.y = start.y + (distance * sin(angle));
			mlx_put_pixel(core()->player, axis.x, axis.y, color);
			distance++;
		}
		start.x = axis.x;
		start.y = axis.y;
		side++;
	}
}

static void	floor_casting(int x_axis, int y_axis, t_tex *tex)
{
	t_uint			index;
	t_uint			color;
	t_uint			offset_x;
	t_uint			offset_y;
	double			distance;
    double          factor;
	t_coordinates	floor;

	t_coordinates	dir;
	t_coordinates	plane;

	dir = (t_coordinates){cos(data()->player.angle), sin(data()->player.angle)};
	plane = (t_coordinates){-dir.y * 0.66, dir.x * 0.66};

	distance = core()->mid_h / (y_axis - core()->mid_h);
	factor = (double)(y_axis - core()->mid_h) / core()->mid_h;
	floor.x = data()->player.pos.x + distance * (dir.x + plane.x * factor);
	floor.y = data()->player.pos.y + distance * (dir.y + plane.y * factor);
	offset_x = (t_uint)(floor.x * tex->width) % tex->width;
	offset_y = (t_uint)(floor.y * tex->height) % tex->height;
	index = (offset_y * tex->width + offset_x) * tex->bytes_per_pixel;
	color = apply_shade_effects(tex->pixels + index, distance);
	mlx_put_pixel(core()->screen, x_axis, y_axis, color);
}
