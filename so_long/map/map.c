/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:18:29 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 16:11:34 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	*join_n_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	if (!res)
		return (free(s1), NULL);
	free(s1);
	return (res);
}

static char	*read_map_string(int fd, int *height)
{
	char	*line;
	char	*map_string;
	int		len;

	map_string = NULL;
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		map_string = join_n_free(map_string, line);
		if (!map_string)
			return (free(line), NULL);
		map_string = join_n_free(map_string, "\n");
		if (!map_string)
			return (free(line), NULL);
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	free(line);
	return (map_string);
}

static int	check_empty_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			return (ft_putstr_fd("error: empty line in map\n", 2), 1);
		i++;
	}
	return (0);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	read_map(const char *file, t_game *g)
{
	int		fd;
	char	*map_string;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("error: failed to open map file\n", 2), 1);
	map_string = read_map_string(fd, &g->height);
	close(fd);
	if (!map_string || map_string[0] == '\0')
		return (free(map_string), ft_putstr_fd("error: empty map\n", 2), 1);
	g->map = ft_split(map_string, '\n');
	free(map_string);
	if (!g->map)
		return (ft_putstr_fd("error: map split failed\n", 2), 1);
	if (check_empty_lines(g->map))
		return (free_map(g->map), g->map = NULL, 1);
	g->width = ft_strlen(g->map[0]);
	return (0);
}
