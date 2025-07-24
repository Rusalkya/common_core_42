/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:30:49 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 16:14:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
}

static char	**dup_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = strdup(map[i]);
		if (!copy[i])
			return (free_map(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	is_map_solvable(char **map, int player_y, int player_x)
{
	int		y;
	int		x;
	char	**copy;

	copy = dup_map(map);
	if (!copy)
		return (0);
	flood_fill(copy, player_y, player_x);
	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
			{
				free_map(copy);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map(copy);
	return (1);
}

static int	is_validname(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(str + len - 4, ".ber", 4) != 0)
		return (1);
	return (0);
}

int	game_is_ok(t_game *g, const char *filename)
{
	if (is_validname(filename))
		return (ft_putstr_fd("error: file is invalid\n", 2), 1);
	if (read_map(filename, g))
		return (1);
	if (validate_map(g))
		return (1);
	find_player(g);
	if (!is_map_solvable(g->map, g->player_y, g->player_x))
		return (ft_putstr_fd("error: map is not solvable\n", 2),
			free_map(g->map), g->map = NULL, 1);
	return (0);
}
