#include "Cub3D.h"

void	draw_line(t_coordinates start, double length, uint color)
{
	double			distance;
	t_coordinates	axis;

	distance = 0.0;
	axis = (t_coordinates){0, 0};
	while (distance < length)
	{
		axis.x = start.x + (distance * cos(data()->player.angle));
		axis.y = start.y + (distance * sin(data()->player.angle));
		mlx_put_pixel(core()->mini_2, axis.x, axis.y, color);
		distance++;
	}
}

void	draw_square(t_coordinates start)
{
	uint			color;
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
			mlx_put_pixel(core()->mini_2, axis.x, axis.y, color);
			distance++;
		}
		start.x = axis.x;
		start.y = axis.y;
		side++;
	}
}
