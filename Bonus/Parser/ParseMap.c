/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:11:55 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/03 18:26:29 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

static void	init_map_loader(void)
{
	char	*line;
	int		lenline;

	lenline = 0;
	while (true)
	{
		data()->map.height++;
		line = get_next_line(data()->map.file);
		if (line == NULL)
			break ;
		if (*line == '\n')
			error_hanlder("Invalid " YELLOW "<Map>" RESET);
		lenline = strlen_set(line, '\n');
		if (lenline > data()->map.width)
			data()->map.width = lenline;
		(data()->map).load = ft_strjoin(data()->map.load, line);
	}
}

static void	normalize_map_shape(char **grid, int longline)
{
	int		index;
	int		lenline;
	char	*newline;

	index = 0;
	while (grid[index])
	{
		lenline = ft_strlen(grid[index]);
		if (lenline < longline)
		{
			newline = allocate(longline + 1, sizeof(char));
			ft_strlcpy(newline, grid[index], lenline + 1);
			ft_memset(newline + lenline, ' ', longline);
			newline[longline] = '\0';
			grid[index] = newline;
		}
		index++;
	}
}

static void	is_map_surrounded(t_map *map, int height)
{
	int		width;
	char	**grid;

	width = -1;
	grid = map->grid;
	while (grid[height][++width])
	{
		if (valid_player_symbols(grid[height][width]) == false
			&& grid[height][width] != '0')
			continue ;
		if (set_player_angle(grid[height][width]) == true)
		{
			data()->player.pos.x = width * TILE + (TILE / 2);
			data()->player.pos.y = height * TILE + (TILE / 2);
		}
		if (!height || !width || !grid[height + 1] || width == map->width - 1
			|| grid[height + 1][width] == ' ' || grid[height - 1][width] == ' '
			|| grid[height][width + 1] == ' ' || grid[height][width - 1] == ' ')
			error_hanlder("Invalid " YELLOW "<Map>" RESET);
	}
}

void	parse_map(void)
{
	int		height;

	height = 0;
	while (true)
	{
		data()->map.load = get_next_line(data()->map.file);
		if (data()->map.load && *data()->map.load == '\n')
			continue ;
		break ;
	}
	init_map_loader();
	if (map_invalid_symbols(data()->map.load) == true)
		error_hanlder("Invalid " YELLOW "<Map>" RESET);
	(data()->map).grid = ft_split(data()->map.load, '\n');
	normalize_map_shape(data()->map.grid, data()->map.width);
	while (data()->map.grid[height])
		is_map_surrounded(&data()->map, height++);
}
