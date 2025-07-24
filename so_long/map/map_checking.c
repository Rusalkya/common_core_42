/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:13:25 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 15:59:49 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_line(char *line, t_counts *counts)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			counts->p++;
		else if (line[i] == 'C')
			counts->c++;
		else if (line[i] == 'E')
			counts->e++;
		else if (line[i] == 'V')
			counts->v++;
		else if (line[i] != '0' && line[i] != '1')
			return (ft_putstr_fd("error: invalid char in map\n", 2), 1);
		i++;
	}
	return (0);
}

static int	check_split_map(char **map, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if (!map[y] || map[y][0] == '\0')
			return (1);
		y++;
	}
	return (0);
}

static int	check_map_walls(t_game *g)
{
	int	x;
	int	y;
	int	last_row;
	int	last_col;

	last_row = g->height - 1;
	last_col = g->width - 1;
	x = 0;
	if (check_split_map(g->map, g->height))
		return (ft_putstr_fd("error: empty line in map\n", 2), 1);
	while (x < g->width)
	{
		if (g->map[0][x] != '1' || g->map[last_row][x] != '1')
			return (ft_putstr_fd("error: map not closed by walls\n", 2), 1);
		x++;
	}
	y = 0;
	while (y < g->height)
	{
		if (g->map[y][0] != '1' || g->map[y][last_col] != '1')
			return (ft_putstr_fd("error: map not closed by walls\n", 2), 1);
		y++;
	}
	return (0);
}

int	validate_map(t_game *g)
{
	int			y;
	t_counts	counts;

	if (g->height < 3 || g->width < 3)
		return (free_map(g->map), ft_putstr_fd("error: map too small\n", 2), 1);
	counts.p = 0;
	counts.c = 0;
	counts.e = 0;
	counts.v = 0;
	y = 0;
	while (g->map[y])
	{
		if ((int)ft_strlen(g->map[y]) != g->width)
			return (free_map(g->map), ft_putstr_fd("error:invalid map\n", 2),
				1);
		if (check_map_line(g->map[y], &counts))
			return (free_map(g->map), 1);
		y++;
	}
	if (counts.p != 1 || counts.c == 0 || counts.e != 1)
		return (free_map(g->map), ft_putstr_fd("error: miss P, C or E\n", 2), 1);
	if (check_map_walls(g))
		return (free_map(g->map), 1);
	g->total_items = counts.c;
	return (0);
}
