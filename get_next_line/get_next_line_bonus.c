/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:35:13 by abbaraka          #+#    #+#             */
/*   Updated: 2023/12/17 13:01:27 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_newline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*fill_line(char *full, int was_read, char *buffer, int fd)
{
	while (!ft_strchr(full, '\n') && was_read)
	{
		buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1));
		if (!buffer)
			return (free(full), full = NULL, NULL);
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read == -1)
			return (free(buffer), buffer = NULL, free(full), full = NULL, NULL);
		buffer[was_read] = '\0';
		full = ft_strjoin(full, buffer);
		free(buffer);
	}
	return (full);
}

char	*get_next_line(int fd)
{
	static char	*full[OPEN_MAX];
	char		*buffer;
	char		*tmp;
	int			was_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	was_read = 1;
	buffer = NULL;
	full[fd] = fill_line(full[fd], was_read, buffer, fd);
	if (!full[fd] || !*full[fd])
		return (free(full[fd]), full[fd] = NULL, NULL);
	if (!ft_strchr(full[fd], '\n') && ft_strchr(full[fd], '\0'))
		return (buffer = ft_strdup(full[fd]), free(full[fd]),
			full[fd] = NULL, buffer);
	buffer = ft_substr(full[fd]);
	if (!buffer)
		return (free(full[fd]), full[fd] = NULL, NULL);
	tmp = ft_strdup(full[fd] + check_newline(full[fd]) + 1);
	free(full[fd]);
	full[fd] = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (buffer);
}
