/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:55:47 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_player_pos(t_hub *hub)
{
	int	i;
	int	j;

	i = 0;
	while (hub->map[i])
	{
		j = 0;
		while (hub->map[i][j])
		{
			if (hub->map[i][j] == 'N' || hub->map[i][j] == 'S'
				|| hub->map[i][j] == 'E' || hub->map[i][j] == 'W')
			{
				hub->player->posx = j + 0.5;
				hub->player->posy = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	init_player_direction_2(t_hub *hub, char player_char)
{
	if (player_char == 'S')
	{
		hub->player->dirx = 0.0;
		hub->player->diry = 1.0;
		hub->player->planex = -PLANE_FACTOR;
		hub->player->planey = 0.0;
	}
	else if (player_char == 'N')
	{
		hub->player->dirx = 0.0;
		hub->player->diry = -1.0;
		hub->player->planex = PLANE_FACTOR;
		hub->player->planey = 0.0;
	}
}

static void	init_player_direction(t_hub *hub)
{
	char	player_char;

	player_char = hub->map[(int)hub->player->posy][(int)hub->player->posx];
	if (player_char == 'W')
	{
		hub->player->dirx = -1.0;
		hub->player->diry = 0.0;
		hub->player->planex = 0.0;
		hub->player->planey = -PLANE_FACTOR;
	}
	else if (player_char == 'E')
	{
		hub->player->dirx = 1.0;
		hub->player->diry = 0.0;
		hub->player->planex = 0.0;
		hub->player->planey = PLANE_FACTOR;
	}
	else if (player_char == 'S' || player_char == 'N')
		init_player_direction_2(hub, player_char);
}

void	init_player(t_hub *hub)
{
	if (!hub || !hub->map || !hub->player)
		return ;
	init_player_pos(hub);
	init_player_direction(hub);
	init_hammers(hub);
}
