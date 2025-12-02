/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hammer_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:59:45 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:57:48 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_hammer_list	*create_hammer_node(t_hub *hub, int x, int y)
{
	t_hammer_list	*new_node;

	new_node = malloc(sizeof(t_hammer_list));
	if (!new_node)
	{
		msg_error("Malloc error for hammer.", NULL, NULL);
		ft_exit(hub, 1);
	}
	new_node->hammer = malloc(sizeof(t_hammer));
	if (!new_node->hammer)
	{
		free(new_node);
		msg_error("Malloc error for hammer.", NULL, NULL);
		ft_exit(hub, 1);
	}
	new_node->hammer->x = x;
	new_node->hammer->y = y;
	new_node->hammer->active = 1;
	new_node->hammer->angle = 0.0;
	new_node->next = NULL;
	return (new_node);
}

void	add_hammer(t_hub *hub, int x, int y)
{
	t_hammer_list	*new_node;
	t_hammer_list	*current;

	new_node = create_hammer_node(hub, x, y);
	if (!hub->hammers)
		hub->hammers = new_node;
	else
	{
		current = hub->hammers;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	init_hammers(t_hub *hub)
{
	int	i;
	int	j;

	hub->hammers = NULL;
	hub->has_hammer = 0;
	i = 0;
	while (hub->map[i])
	{
		j = 0;
		while (hub->map[i][j])
		{
			if (hub->map[i][j] == MAP_HAMMER)
				add_hammer(hub, j, i);
			j++;
		}
		i++;
	}
}

void	free_hammers(t_hammer_list *hammers)
{
	t_hammer_list	*current;
	t_hammer_list	*next;

	current = hammers;
	while (current)
	{
		next = current->next;
		if (current->hammer)
			free(current->hammer);
		free(current);
		current = next;
	}
}
