/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:08:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/25 17:47:45 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '2'
		|| c == 'H')
		return (1);
	return (0);
}

static int	check_bounds(char **map_copy, int x, int y)
{
	int	height;
	int	width;

	height = get_map_height(map_copy);
	width = get_map_width(map_copy);
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	if (x >= (int)ft_strlen(map_copy[y]))
		return (0);
	return (1);
}

static void	flood_fill(char **map_copy, int x, int y, int *error)
{
	if (!check_bounds(map_copy, x, y))
	{
		*error = 1;
		return ;
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return ;
	if (map_copy[y][x] == ' ')
	{
		*error = 1;
		return ;
	}
	if (!is_valid_char(map_copy[y][x]))
	{
		*error = 1;
		return ;
	}
	map_copy[y][x] = 'V';
	flood_fill(map_copy, x + 1, y, error);
	flood_fill(map_copy, x - 1, y, error);
	flood_fill(map_copy, x, y + 1, error);
	flood_fill(map_copy, x, y - 1, error);
}

void	check_map_closed(t_hub *hub)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		error;
	int		i;

	error = 0;
	find_player_pos(hub->map, &player_x, &player_y);
	map_copy = copy_map(hub->map);
	if (!map_copy)
	{
		msg_error("Error: Memory allocation failed", NULL, NULL);
		ft_exit(hub, 1);
	}
	flood_fill(map_copy, player_x, player_y, &error);
	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
	if (error)
	{
		msg_error("Error: Map is not closed or has invalid spaces", NULL, NULL);
		ft_exit(hub, 1);
	}
}
