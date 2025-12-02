/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:54:34 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:55:47 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**resize_map_array(char **map, int old_size, int new_size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

char	*clean_map_line(char *line)
{
	char	*clean_line;
	int		len;

	if (!line)
		return (NULL);
	clean_line = ft_strdup(line);
	if (!clean_line)
		return (NULL);
	len = ft_strlen(clean_line);
	if (len > 0 && clean_line[len - 1] == '\n')
		clean_line[len - 1] = '\0';
	return (clean_line);
}

char	**process_map_line(char **map, char *line, int *line_count,
		int *map_started)
{
	if (!*map_started && is_map_line(line))
		*map_started = 1;
	if (*map_started)
	{
		map = resize_map_array(map, *line_count, *line_count + 1);
		if (!map)
			return (NULL);
		map[*line_count] = clean_map_line(line);
		map[++(*line_count)] = NULL;
	}
	return (map);
}

int	open_map_file(char *filename, t_hub *hub)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		msg_error("Cannot open file", filename, NULL);
		ft_exit(hub, 1);
	}
	return (fd);
}

void	parse_map(char *filename, t_hub *hub)
{
	if (!filename || !hub)
		return ;
	hub->map = read_map_from_file(filename, hub);
	if (!hub->map)
	{
		msg_error("Failed to read map from file", filename, NULL);
		ft_exit(hub, 1);
	}
	check_map_char(hub);
	check_player(hub->map, hub);
	check_cracked_walls(hub);
}
