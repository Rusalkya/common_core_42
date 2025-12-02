/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:20:49 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/26 11:50:09 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	verif_draw_minimap(int x, int y)
{
	int	dx;
	int	dy;
	int	r2;

	dx = x - MN_CX;
	dy = y - MN_CY;
	r2 = MN_R * MN_R;
	if (dx * dx + dy * dy <= r2)
		return (1);
	return (0);
}

static void	draw_case(t_hub *hub, int x, int y, int color)
{
	int	base_x;
	int	base_y;
	int	i;
	int	j;

	base_x = MN_CX + (int)((x - hub->player->posx) * MINIMAP_SCALE);
	base_y = MN_CY + (int)((y - hub->player->posy) * MINIMAP_SCALE);
	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			if (verif_draw_minimap(base_x + j, base_y + i))
				put_px(hub->frame, base_x + j, base_y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_img *frame)
{
	int	radius;
	int	x;
	int	y;
	int	r2;

	radius = MINIMAP_SCALE / 10;
	y = -radius;
	r2 = radius * radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= r2)
				put_px(frame, MN_CX + x, MN_CY + y, PLAYER);
			x++;
		}
		y++;
	}
}

static void	draw_minimap(t_hub *hub)
{
	int	y;
	int	x;

	y = 0;
	while (hub->map[y])
	{
		x = 0;
		while (hub->map[y][x])
		{
			if (hub->map[y][x] == '1')
				draw_case(hub, x, y, MN_1);
			else if (hub->map[y][x] == '2' || hub->map[y][x] == '3'
				|| hub->map[y][x] == '4')
				draw_case(hub, x, y, 0x808080);
			else
				draw_case(hub, x, y, MN_0);
			x++;
		}
		y++;
	}
}

void	minimap(t_hub *hub)
{
	draw_minimap(hub);
	draw_rays_on_minimap(hub, hub->ray);
	draw_player(hub->frame);
}
