/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_screamer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 12:40:13 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_final_screamer(t_hub *hub)
{
	if (!hub->final_screamer_active)
		return ;
	hub->final_screamer_counter++;
	if (hub->final_screamer_counter >= 15)
	{
		hub->final_screamer_frame = 1 - hub->final_screamer_frame;
		hub->final_screamer_counter = 0;
	}
	if (hub->fade_to_black_progress < 360)
		hub->fade_to_black_progress++;
}

void	render_final_fade(t_hub *hub)
{
	int				x;
	int				y;
	int				alpha;
	unsigned int	color;
	unsigned int	black_overlay;

	if (!hub->final_screamer_active || hub->fade_to_black_progress == 0)
		return ;
	alpha = (hub->fade_to_black_progress * 255) / 360;
	if (alpha > 255)
		alpha = 255;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = get_px(hub->frame, x, y);
			black_overlay = ((alpha << 24) | 0x000000);
			color = ((color & 0xFFFFFF) * (255 - alpha)) / 255;
			put_px(hub->frame, x, y, color);
			x++;
		}
		y++;
	}
}
