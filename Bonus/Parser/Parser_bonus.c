/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:37:59 by abadouab          #+#    #+#             */
/*   Updated: 2024/11/15 09:20:24 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

static bool	valid_elements(void)
{
	if (data()->colors.setceiling && data()->colors.setfloor
		&& data()->textures.north && data()->textures.south
		&& data()->textures.west && data()->textures.east)
		return (true);
	return (false);
}

bool	duplicated_elements(char set)
{
	if ((set == 'N' && data()->textures.north)
		|| (set == 'S' && data()->textures.south)
		|| (set == 'W' && data()->textures.west)
		|| (set == 'E' && data()->textures.east)
		|| (set == 'F' && data()->colors.floor)
		|| (set == 'C' && data()->colors.ceiling))
		error_hanlder("Invalid " YELLOW "<Map>" RESET);
	return (true);
}

static void	parse_elements(char *object)
{
	if (ft_strncmp(object, "EA ", ft_strlen("EA ")) == 0)
		data()->textures.east = parse_texture(object);
	else if (ft_strncmp(object, "WE ", ft_strlen("WE ")) == 0)
		data()->textures.west = parse_texture(object);
	else if (ft_strncmp(object, "SO ", ft_strlen("SO ")) == 0)
		data()->textures.south = parse_texture(object);
	else if (ft_strncmp(object, "NO ", ft_strlen("NO ")) == 0)
		data()->textures.north = parse_texture(object);
	else if (ft_strncmp(object, "C ", ft_strlen("C ")) == 0)
		data()->colors.ceiling = parse_color(object);
	else if (ft_strncmp(object, "F ", ft_strlen("F ")) == 0)
		data()->colors.floor = parse_color(object);
	else if (*object)
	{
		close(data()->map.file);
		error_hanlder("Invalid " YELLOW "<Map>" RESET);
	}
}

void	parser(void)
{
	if (data()->map.file != 2)
		error_hanlder(YELLOW "Usage: "RESET "./Cub3d <filename.ber>");
	if (ft_strrchr(data()->map.load, '.') == NULL
		|| ft_strcmp(ft_strrchr(data()->map.load, '.'), ".cub"))
		error_hanlder("Input must have " YELLOW "\".cub\"" RESET " extension.");
	(data()->map).file = open(data()->map.load, O_RDONLY);
	if (data()->map.file == ERROR)
		error_hanlder("Invalid: " YELLOW "<filename.ber>");
	while (valid_elements() == false)
	{
		(data()->map).load = ft_strtrim(get_next_line(data()->map.file), " \n");
		if (data()->map.load == NULL)
			break ;
		parse_elements(data()->map.load);
	}
	if (valid_elements() == false)
		error_hanlder("Invalid " YELLOW "<Map>" RESET);
	parse_map();
}
