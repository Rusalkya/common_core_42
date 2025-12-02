/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_hammer_attack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:12:13 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/25 12:03:25 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	get_wall_in_front(t_hub *hub)
{
	int		check_x;
	int		check_y;
	double	check_dist;

	check_dist = 1.5;
	check_x = (int)(hub->player->posx + hub->player->dirx * check_dist);
	check_y = (int)(hub->player->posy + hub->player->diry * check_dist);
	if (check_y < 0 || check_x < 0)
		return ('0');
	if (!hub->map[check_y] || !hub->map[check_y][check_x])
		return ('0');
	return (hub->map[check_y][check_x]);
}

static void	modify_wall_in_front(t_hub *hub, char new_char)
{
	int		check_x;
	int		check_y;
	double	check_dist;

	check_dist = 1.5;
	check_x = (int)(hub->player->posx + hub->player->dirx * check_dist);
	check_y = (int)(hub->player->posy + hub->player->diry * check_dist);
	if (check_y < 0 || check_x < 0)
		return ;
	if (!hub->map[check_y] || !hub->map[check_y][check_x])
		return ;
	hub->map[check_y][check_x] = new_char;
}

void	start_hammer_attack(t_hub *hub)
{
	char	wall;

	if (!hub->has_hammer || hub->pov->is_attacking)
		return ;
	wall = get_wall_in_front(hub);
	if (wall == '2' || wall == '3' || wall == '4')
		play_hammer_sound();
	else
		play_air_hit_sound();
	hub->pov->is_attacking = 1;
	hub->pov->attack_frame = 0;
	if (wall == '2')
		hub->pov->attack_type = 1;
	else if (wall == '3')
		hub->pov->attack_type = 2;
	else if (wall == '4')
		hub->pov->attack_type = 3;
	else
		hub->pov->attack_type = 0;
}

static void	finish_attack(t_hub *hub)
{
	if (hub->pov->attack_type == 1)
		modify_wall_in_front(hub, '3');
	else if (hub->pov->attack_type == 2)
		modify_wall_in_front(hub, '4');
	else if (hub->pov->attack_type == 3)
		modify_wall_in_front(hub, '5');
	hub->pov->is_attacking = 0;
	hub->pov->attack_frame = 0;
}

void	update_hammer_attack(t_hub *hub)
{
	int	threshold_air;
	int	threshold_wall;

	if (!hub->pov->is_attacking)
		return ;
	hub->pov->attack_frame++;
	threshold_air = 20;
	threshold_wall = 25;
	if (hub->key->ctrl)
	{
		threshold_air = 17;
		threshold_wall = 21;
	}
	if (hub->pov->attack_type == 0)
	{
		if (hub->pov->attack_frame >= threshold_air)
			finish_attack(hub);
	}
	else
	{
		if (hub->pov->attack_frame >= threshold_wall)
			finish_attack(hub);
	}
}
