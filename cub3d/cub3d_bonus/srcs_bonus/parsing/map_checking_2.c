/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:10:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:25:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_on_edge(char **map, int i, int j)
{
	int	map_height;
	int	line_len;

	map_height = 0;
	while (map[map_height])
		map_height++;
	line_len = ft_strlen(map[i]);
	if (i == 0 || i == map_height - 1)
		return (1);
	if (j == 0 || j == line_len - 1)
		return (1);
	return (0);
}

void	check_cracked_walls(t_hub *hub)
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
			if (map[i][j] == '2' && is_on_edge(map, i, j))
			{
				msg_error("Cracked wall ('2') cannot be on map edges.", NULL,
					NULL);
				ft_exit(hub, 1);
			}
			j++;
		}
		i++;
	}
}
