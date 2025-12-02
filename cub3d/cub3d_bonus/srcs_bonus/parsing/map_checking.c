/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:50:37 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:55:47 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_map_char(t_hub *hub)
{
	int		i;
	int		j;
	char	**map;

	map = hub->map;
	if (!hub || !map)
		return ;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ' && map[i][j] != '2' && map[i][j] != 'H'
				&& map[i][j] != '3' && map[i][j] != '4' && map[i][j] != '5')
			{
				msg_error("Invalid character in map.", NULL, NULL);
				ft_exit(hub, 1);
			}
			j++;
		}
		i++;
	}
}

void	check_player(char **map, t_hub *hub)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0 || player_count > 1)
	{
		msg_error("There must be exactly one player on the map.", NULL, NULL);
		ft_exit(hub, 1);
	}
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	return (line[i] == '1' || line[i] == '0');
}
