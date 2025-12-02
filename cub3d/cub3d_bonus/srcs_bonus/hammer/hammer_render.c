/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hammer_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:06:58 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:57:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_hammer_pixel(t_hub *hub, int screen_x, int screen_y,
		unsigned int color)
{
	if (screen_x >= 0 && screen_x < WIN_W && screen_y >= 0 && screen_y < WIN_H)
		put_px(hub->frame, screen_x, screen_y, color);
}

static void	draw_simple_hammer(t_hub *hub, int cx, int cy)
{
	int	i;
	int	j;

	i = -4;
	while (i <= 4)
	{
		j = -4;
		while (j <= 4)
		{
			draw_hammer_pixel(hub, cx + i, cy + j, 0xFFD700);
			j++;
		}
		i++;
	}
}

static void	render_single_hammer(t_hub *hub, t_hammer *hammer)
{
	int	screen_x;
	int	screen_y;
	int	map_center_x;
	int	map_center_y;

	if (!hammer->active)
		return ;
	map_center_x = hammer->x * MINIMAP_SCALE + MINIMAP_SCALE / 2;
	map_center_y = hammer->y * MINIMAP_SCALE + MINIMAP_SCALE / 2;
	screen_x = MN_CX + (map_center_x - (int)(hub->player->posx
				* MINIMAP_SCALE));
	screen_y = MN_CY + (map_center_y - (int)(hub->player->posy
				* MINIMAP_SCALE));
	if (screen_x < MN_CX - MN_R || screen_x > MN_CX + MN_R || screen_y < MN_CY
		- MN_R || screen_y > MN_CY + MN_R)
		return ;
	draw_simple_hammer(hub, screen_x, screen_y);
}

void	render_hammers(t_hub *hub)
{
	t_hammer_list	*current;

	current = hub->hammers;
	while (current)
	{
		render_single_hammer(hub, current->hammer);
		current = current->next;
	}
}
