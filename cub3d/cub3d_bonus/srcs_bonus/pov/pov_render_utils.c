/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:39:45 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:56:17 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_img	*get_attacking_sprite(t_hub *hub)
{
	if (hub->pov->attack_frame < 5)
		return (hub->pov->hammer_hit1);
	else if (hub->pov->attack_frame < 10)
		return (hub->pov->hammer_hit2);
	else if (hub->pov->attack_frame < 10)
		return (hub->pov->hammer_hit3);
	else if (hub->pov->attack_type == 0)
		return (hub->pov->hammer_hit2);
	else if (hub->pov->attack_type == 1)
		return (hub->pov->hammer_pow);
	else if (hub->pov->attack_type == 2)
		return (hub->pov->hammer_crack);
	else
		return (hub->pov->hammer_boom);
}

t_img	*get_current_pov_sprite(t_hub *hub)
{
	if (hub->pov->is_attacking)
		return (get_attacking_sprite(hub));
	if (hub->has_hammer)
	{
		if (hub->pov->current_frame == 0)
			return (hub->pov->hammer1);
		else
			return (hub->pov->hammer2);
	}
	else
	{
		if (hub->pov->current_frame == 0)
			return (hub->pov->empty1);
		else
			return (hub->pov->empty2);
	}
}

int	is_transparent(unsigned int color)
{
	if (color == 0xFF00FF || color == 0x00FF00FF || color == 0xFFFF00FF)
		return (1);
	if ((color & 0x00FFFFFF) == 0x00FF00FF)
		return (1);
	return (0);
}
