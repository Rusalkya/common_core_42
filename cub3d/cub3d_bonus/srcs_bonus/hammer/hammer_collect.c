/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hammer_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:10:51 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 14:40:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_near_hammer(t_player *player, t_hammer *hammer)
{
	double	dx;
	double	dy;
	double	distance;

	dx = player->posx - (hammer->x + 0.5);
	dy = player->posy - (hammer->y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	return (distance < 0.5);
}

static void	collect_hammer(t_hub *hub, t_hammer *hammer)
{
	hammer->active = 0;
	hub->has_hammer = 1;
	hub->map[hammer->y][hammer->x] = '0';
}

static void	remove_hammer_node(t_hammer_list **prev_next,
		t_hammer_list *to_remove)
{
	*prev_next = to_remove->next;
	free(to_remove->hammer);
	free(to_remove);
}

void	check_hammer_collect(t_hub *hub)
{
	t_hammer_list	*current;
	t_hammer_list	**prev_next;

	prev_next = &hub->hammers;
	current = hub->hammers;
	while (current)
	{
		if (current->hammer->active && is_near_hammer(hub->player,
				current->hammer))
		{
			collect_hammer(hub, current->hammer);
			remove_hammer_node(prev_next, current);
			current = *prev_next;
		}
		else
		{
			prev_next = &current->next;
			current = current->next;
		}
	}
}
