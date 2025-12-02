/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hammer_world_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:00:26 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 14:40:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_hammer_pixel(t_hub *hub, int x, int y, int color)
{
	if (y >= 0 && y < WIN_H && x >= 0 && x < WIN_W)
		if ((color & 0x00FFFFFF) != 0x00FF00FF)
			put_px(hub->frame, x, y, color);
}

static void	render_stripe(t_hub *hub, t_hammer_draw *d, int stripe, int h)
{
	int	y;
	int	s;
	int	e;
	int	tx;
	int	ty;

	get_tex_coord(&tx, stripe, hub, h);
	s = (WIN_H - h) / 2;
	e = s + h;
	if (s < 0)
		s = 0;
	if (e >= WIN_H)
		e = WIN_H - 1;
	y = s;
	while (y < e)
	{
		ty = (y - s) * hub->mlx->hammer_sprite->h / h;
		if (ty >= 0 && ty < hub->mlx->hammer_sprite->h)
			draw_hammer_pixel(hub, d->screen_x, y,
				*(unsigned int *)(hub->mlx->hammer_sprite->addr
					+ ty * hub->mlx->hammer_sprite->line
					+ tx * (hub->mlx->hammer_sprite->bpp / 8)));
		y++;
	}
}

static void	render_hammer_stripes(t_hub *hub, t_hammer_draw *d)
{
	int	i;
	int	sw;

	sw = d->sprite_height;
	i = 0;
	while (i < sw)
	{
		d->screen_x = (int)((WIN_W / 2) * (1 + tan(d->relative_angle)
					/ tan(M_PI / 3))) - sw / 2 + i;
		if (d->screen_x >= 0 && d->screen_x < WIN_W)
			render_stripe(hub, d, i, d->sprite_height);
		i++;
	}
}

static void	render_single_hammer(t_hub *hub, t_hammer *hammer)
{
	t_hammer_draw	d;

	init_hammer_draw(&d, hub, hammer);
	if (d.distance > 0.1 && d.distance < 20)
	{
		calc_hammer_screen_pos(&d, hub);
		if (fabs(d.relative_angle) < M_PI / 2)
			render_hammer_stripes(hub, &d);
	}
}

void	render_hammers_in_world(t_hub *hub)
{
	t_hammer_list	*current;

	current = hub->hammers;
	while (current)
	{
		if (current->hammer->active)
			render_single_hammer(hub, current->hammer);
		current = current->next;
	}
}
