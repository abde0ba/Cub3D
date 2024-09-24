/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:42:51 by abbaraka          #+#    #+#             */
/*   Updated: 2024/09/24 18:40:32 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void ft_put_pixel(t_data *data,char color, int x, int y)
{
	int i;
	int j;

	i = y * TILE;
	while (i < y * TILE + TILE)
	{
		j = x * TILE;
		while ( j < x * TILE + TILE)
		{
			if (color == 'r')
				mlx_put_pixel(data->image, i, j, ft_pixel(255, 0, 0, 255));
			else if (color == 'b')
				mlx_put_pixel(data->image, i, j, ft_pixel(0, 0, 0, 255));
			else if (color == 'y')
				mlx_put_pixel(data->image, i, j, ft_pixel(255, 255, 0, 255));
			j++;
		}
		i++;
	}
}
void	render_map(t_data *data)
{
	int x = 0;
	
	while (data->map[x])
	{
		int y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				ft_put_pixel(data, 'r', x, y);
			else if (data->map[x][y] == '0' || data->map[x][y] == 'N')
				ft_put_pixel(data, 'b', x, y);
			y++;			
		}
		x++;
	}
}

void	ft_print_player(t_data *data, int x, int y, int size)
{
	int i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
		{
			mlx_put_pixel(data->image, j, i, ft_pixel(255, 255, 0, 255));
			j++;
		}
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (dstsize != 0)
	{
		while (j < dstsize - 1 && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (i);
}

static int	check_set(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*ptr;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	while ((check_set(s1[start], set) == 1) && (start <= end))
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while ((check_set(s1[end], set) == 1) && (end >= 0))
		end--;
	ptr = (char *)malloc(end - start + 2);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], end - start + 2);
	return (ptr);
}

int	check_player_in_wall(t_data *data, double y, double x)
{
	int	index_x;
	int	index_y;
	int	len_x;
	int	len_y;

	index_y = floor(y / TILE);
	index_x = floor(x / TILE);
	len_y = 0;
	while (data->map[len_y])
		len_y++;
	len_x = ft_strlen(data->map[0]);
	// while (len_y > index_y && data->map[index_y][len_x])
	// 	len_x++;
	// printf("index x :%d index y :%d\n", index_x, index_y);
	if (len_y > index_y && len_x > index_x && data->map[index_y][index_x] == '1')
		return (1);
	return (0);
}

double	ranging_angle(double angle)
{
	double	angle_range;

	angle_range = remainder(angle, (2 * M_PI));
	if (angle_range < 0)
		angle_range += 2 * M_PI;
	return (angle_range);
}

int	check_ray_dir_down_up(double angle)
{
	if (angle > 0 && angle < M_PI)
			return (1);
	return (0);
}

int	check_ray_dir_righ_left(double angle)
{
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
			return (1);
	return (0);
}

void	print_line(t_data *data, double start_y, double start_x, double end_y, double end_x)
{
	int		i;
	double	steps;
	double	x_steps;
	double	y_steps;

	if (fabs(end_x - start_x) > fabs(end_y - start_y))
		steps = fabs(end_x - start_x);
	else
		steps = fabs(end_y - start_y);
	x_steps = (end_x - start_x) / steps;
	y_steps = (end_y - start_y) / steps;
	i = 0;
	while (i < steps)
	{
		mlx_put_pixel(data->image, start_x, start_y, ft_pixel(255, 255, 0, 255));
		start_x += x_steps;
		start_y += y_steps;
		i++;
	}
}

double	calc_dist(fx, fy, sx, sy)
{
	return (sqrt((sx - fx) * (sx - fx) + (sy - fy) * (sy - fy)));
}

int	cast_the_ray_horz(t_data *data, t_ray *ray)
{
	double	inter_x;
	double	inter_y;
	double	next_on_wallx;
	double	next_on_wally;
	double	check_next_on_wally;
	double	step_x;
	double	step_y;

	inter_y = TILE * floor(data->player->y_pos / TILE);
	if (check_ray_dir_down_up(ray->angle))
		inter_y += TILE;
	inter_x = data->player->x_pos + (inter_y - data->player->y_pos) / tan(ray->angle);
	step_y = TILE;
	if (!check_ray_dir_down_up(ray->angle))
		step_y *= -1;
	step_x = (TILE * (inter_x - data->player->x_pos)) / (inter_y - data->player->y_pos);
	if (check_ray_dir_righ_left(ray->angle) && step_x < 0)
		step_x *= -1;
	if (!check_ray_dir_righ_left(ray->angle) && step_x > 0)
		step_x *= -1;
	next_on_wallx = inter_x;
	next_on_wally = inter_y;
	while (next_on_wallx >= 0 && next_on_wallx < WIDTH && next_on_wally >= 0 && next_on_wally < HEIGHT)
	{
		check_next_on_wally = next_on_wally;
		if (!check_ray_dir_down_up(ray->angle))
			check_next_on_wally--;
		if (check_player_in_wall(data, check_next_on_wally, next_on_wallx))
		{
			ray->wall_horz_x = next_on_wallx;
			ray->wall_horz_y = next_on_wally;
			return (1);
		}
		else
		{
			next_on_wallx += step_x;
			next_on_wally += step_y;
		}
	}
	return (0);
}

int	cast_the_ray_vert(t_data *data, t_ray *ray)
{
	double	inter_x;
	double	inter_y;
	double	next_on_wallx;
	double	check_next_on_wallx;
	double	next_on_wally;
	double	step_x;
	double	step_y;

	inter_x = TILE * floor(data->player->x_pos / TILE);
	if (check_ray_dir_righ_left(ray->angle))
		inter_x += TILE;
	inter_y = data->player->y_pos + ((inter_x - data->player->x_pos) * tan(ray->angle));
	step_x = TILE;
	if (!check_ray_dir_righ_left(ray->angle))
		step_x *= -1;
	step_y = (TILE * (inter_y - data->player->y_pos)) / (inter_x - data->player->x_pos);
	if (!check_ray_dir_down_up(ray->angle) && step_y > 0)
		step_y *= -1;
	if (check_ray_dir_down_up(ray->angle) && step_y < 0)
		step_y *= -1;
	next_on_wallx = inter_x;
	next_on_wally = inter_y;
	while (next_on_wallx >= 0 && next_on_wallx <= WIDTH && next_on_wally >= 0 && next_on_wally <= HEIGHT)
	{
		check_next_on_wallx = next_on_wallx;
		if (!check_ray_dir_righ_left(ray->angle))
			check_next_on_wallx--;
		if (check_player_in_wall(data, next_on_wally, check_next_on_wallx))
		{
			ray->wall_vert_x = next_on_wallx;
			ray->wall_vert_y = next_on_wally;
			return (1);
		}
		else
		{
			next_on_wallx += step_x;
			next_on_wally += step_y;
		}
	}
	return (0);
}

void	cast_the_ray(t_data *data, int i)
{
	t_ray	ray;
	double	horz_touch;
	double	vert_touch;

	ray = data->rays[i];
	horz_touch = 0;
	vert_touch = 0;
	if (cast_the_ray_horz(data, &ray))
	{
		horz_touch = calc_dist(data->player->x_pos, data->player->y_pos, \
		ray.wall_horz_x, ray.wall_horz_y);
	}
	else
		horz_touch = MAXFLOAT;
	if (cast_the_ray_vert(data, &ray))
	{
		vert_touch = calc_dist(data->player->x_pos, data->player->y_pos, \
		ray.wall_vert_x, ray.wall_vert_y);
		// printf("vert_touch :%f\n", vert_touch);
	}
	else
		vert_touch = MAXFLOAT;
	if (horz_touch > vert_touch)
	{
		// print_line(data->player->y_pos, data->player->x_pos, ray.wall_vert_y, ray.wall_vert_x);
		ray.distance = vert_touch;
	}
	else
	{
		// print_line(data->player->y_pos, data->player->x_pos, ray.wall_horz_y, ray.wall_horz_x);
		ray.distance = horz_touch;
	}
	data->rays[i] = ray;
}

void	raycasting(t_data *data)
{
	int		i;
	// int		h;
	double	angle;
	t_ray	*rays;

	i = 0;
	angle = ranging_angle(data->player->angle - (FOV / 2));
	rays = malloc(WIDTH * sizeof(t_ray));
	data->rays = rays;
	while (i < WIDTH)
	{
		rays[i].wall_horz_x = 0;
		rays[i].wall_horz_y = 0;
		rays[i].wall_vert_x = 0;
		rays[i].wall_vert_y = 0;
		rays[i].distance = 0;
		rays[i].col_i = i;
		rays[i].angle = ranging_angle(angle);
		cast_the_ray(data, i);
		// h = 0;
		// while (h < 50)
		// {
		// 	mlx_put_pixel(image, data->player->x_pos + cos(rays[i].angle) * h, data->player->y_pos + sin(rays[i].angle) * h, ft_pixel(255, 255, 0, 255));
		// 	h++;
		// }
		angle +=(FOV / (WIDTH));
		i++;
	}
}

void draw_rect(t_data *data, double x, double y, double height)
{
	int	j;
	double	alpha;
	
	alpha = (200 / data->rays[(int)x].distance) * 15;
	if (alpha > 255)
		alpha = 255;
	j = 0;
	while (j < height)
	{
		mlx_put_pixel(data->image, x, y + j, ft_pixel(255, 255, 255, alpha));
		j++;
	}
}

void	render_walls(t_data *data)
{
	int		i;
	double	ray_distance;
	double	distance_proj_plane;
	double	wall_strip_height;

	i = 0;
	while (i < WIDTH)
	{
		ray_distance = data->rays[i].distance * cos(data->rays[i].angle - data->player->angle);
		distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
		wall_strip_height = (TILE / ray_distance) * distance_proj_plane;
		if (wall_strip_height > HEIGHT)
			wall_strip_height = HEIGHT;
		if (distance_proj_plane > WIDTH)
			distance_proj_plane = WIDTH;
		draw_rect(data, i, (HEIGHT / 2) - (wall_strip_height / 2), wall_strip_height);
		i++;
	}
}

void	move_player(t_data *data)
{
	double	x;
	double	y;
	double	step;

	step = 0;
	data->player->angle += data->player->rot_dir * data->player->rot_speed;
	step = data->player->walk_dir * data->player->walk_speed;
	x = data->player->x_pos + cos(data->player->angle) * step;
	y = data->player->y_pos + sin(data->player->angle) * step;
	if (!check_player_in_wall(data, y + 10, x + 10))
	{
		if (!check_player_in_wall(data, data->player->y_pos, x)
			&& !check_player_in_wall(data, y, data->player->x_pos))
		{	
			data->player->x_pos = x;
			data->player->y_pos = y;
		}
	}
}

void	render(t_data *data)
{
	render_walls(data);
	render_map(data);
	ft_print_player(data, data->player->x_pos - 5, data->player->y_pos - 5, 11);
}

void ft_hook(void* param)
{
	t_data* data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->rot_dir = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->rot_dir = 1;
	move_player(data);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	raycasting(data);
	render(data);
	//printf("cos is %f and sin is %f\n", cos(data->player->angle), sin(data->player->angle));
	free(data->rays);
	data->player->rot_dir = 0;
	data->player->walk_dir = 0;
	//printf("Angle :%f\n", data->player->angle * 180 / M_PI);
}


char	**put_map(char *arg)
{
	int		fd;
	char	*str;
	char	**map;
	int		len;
	int		i;

	(1) && (len = 0, fd = open(arg, O_RDONLY, 777), str = get_next_line(fd),
	len += 1);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		len++;
	}
	(1) && (map = malloc((len + 1) * sizeof(char *)), close(fd),
	fd = open(arg, O_RDONLY, 777), str = get_next_line(fd), i = 0,
	map[i] = ft_strdup(str), i++);
	while (i < len)
	{
		free(str);
		str = get_next_line(fd);
		map[i] = ft_strtrim(str, "\n");
		i++;
	}
	return (map);
}

void	get_player_pos(t_data *data)
{
	int x;
	int y;

		y = 0;
	while (data->map[y])
	{
	x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'W'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'S')
				{
					data->player->x_pos = x * TILE + (TILE / 2);
					data->player->y_pos = y * TILE + (TILE / 2);
				}
		x++;
		}
			y++;			
	}
}

void	init_player(t_data *data)
{
	t_player	*player;

	player = data->player;
	player->angle = ranging_angle(M_PI / 2);
	player->rot_speed = (M_PI / 180);
	player->walk_speed = TILE / 20;
	player->rot_dir = 0;
	player->walk_dir = 0;
	data->player = player;
}

int32_t main(int ac, char **av)
{
	t_data *data;
	t_player *player;

	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	data->player = player;
	init_player(data);
	if (!ac)
		return (0);
	data->map = put_map(av[1]);
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	get_player_pos(data);
	render_map(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	return (EXIT_SUCCESS);
}
