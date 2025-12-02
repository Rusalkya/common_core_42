/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:23:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:24:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_wasd_keys(t_hub *hub, int *is_moving)
{
	if (hub->key->w)
	{
		move_player(hub, 1);
		*is_moving = 1;
	}
	if (hub->key->s)
	{
		move_player(hub, 2);
		*is_moving = 1;
	}
	if (hub->key->a)
	{
		move_player(hub, 3);
		*is_moving = 1;
	}
	if (hub->key->d)
	{
		move_player(hub, 4);
		*is_moving = 1;
	}
}

void	process_movement(t_hub *hub)
{
	int	is_moving;

	is_moving = 0;
	handle_wasd_keys(hub, &is_moving);
	if (hub->key->r)
		rotate_player(hub->player, 1);
	if (hub->key->l)
		rotate_player(hub->player, 2);
	if (!is_moving)
		stop_footstep_sound(hub);
}
