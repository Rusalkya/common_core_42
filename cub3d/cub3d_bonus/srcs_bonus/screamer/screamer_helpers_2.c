/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screamer_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:54:12 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_screamer_display(t_hub *hub, long long current_time,
		long long *last_time)
{
	if (current_time - *last_time >= 10)
	{
		if (hub->screamer_display_time == 0)
			play_screamer_sound();
		hub->screamer_display_time += 10;
		if (hub->screamer_display_time >= 500)
		{
			hub->show_screamer = 0;
			hub->screamer_display_time = 0;
			hub->screamer_sound_played = 0;
			*last_time = current_time;
		}
		else if (hub->screamer_display_time == 0)
		{
			play_screamer_sound();
			hub->screamer_sound_played = 1;
		}
	}
}

void	render_red_filter_loop(t_hub *hub, int time_elapsed)
{
	int				x;
	int				y;
	int				alpha;
	unsigned int	red_color;

	alpha = (time_elapsed * 180) / 100;
	if (alpha > 180)
		alpha = 180;
	red_color = (alpha << 24) | 0x00FF0000;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if ((x + y) % 3 == 0)
			{
				put_px(hub->frame, x, y, ((get_px(hub->frame, x,
								y) & 0x00FEFEFE) >> 1)
					+ ((red_color & 0x00FEFEFE) >> 1));
			}
			x++;
		}
		y++;
	}
}

void	free_screamers(t_hub *hub)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (hub->mlx->screamers[i] && hub->mlx->screamers[i]->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->mlx->screamers[i]->ptr);
		free(hub->mlx->screamers[i]);
		i++;
	}
}
