/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:31:25 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:56:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_if_moving(t_hub *hub)
{
	if (hub->key->w || hub->key->s || hub->key->a || hub->key->d)
		return (1);
	return (0);
}

void	update_pov_animation(t_hub *hub)
{
	int	speed;

	if (!hub->pov)
		return ;
	hub->is_moving = check_if_moving(hub);
	if (hub->is_moving)
	{
		hub->pov->frame_counter++;
		speed = hub->pov->animation_speed;
		if (hub->key->ctrl)
			speed = 8;
		if (hub->pov->frame_counter >= speed)
		{
			hub->pov->current_frame = 1 - hub->pov->current_frame;
			hub->pov->frame_counter = 0;
		}
	}
	else
	{
		hub->pov->current_frame = 0;
		hub->pov->frame_counter = 0;
	}
}
