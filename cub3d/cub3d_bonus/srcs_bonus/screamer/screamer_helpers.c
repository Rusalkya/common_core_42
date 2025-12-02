/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screamer_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 12:52:28 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_screamer_display(t_hub *hub, long long current_time,
			long long *last_time);
void	render_red_filter_loop(t_hub *hub, int time_elapsed);
void	free_screamers(t_hub *hub);

static void	draw_screamer_pixel(t_hub *hub, t_img *screamer, int *pos, int *s)
{
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	if (s[0] + pos[0] >= 0 && s[1] + pos[1] >= 0)
	{
		tex_x = (pos[0] * screamer->w) / s[2];
		tex_y = (pos[1] * screamer->h) / s[3];
		if (tex_x >= 0 && tex_x < screamer->w && tex_y >= 0
			&& tex_y < screamer->h)
		{
			color = get_px(screamer, tex_x, tex_y);
			if (!is_transparent(color))
				put_px(hub->frame, s[0] + pos[0], s[1] + pos[1], color);
		}
	}
}

void	render_screamer_loop(t_hub *hub, t_img *screamer, int *s)
{
	int	x;
	int	y;
	int	pos[2];

	y = 0;
	while (y < s[3] && (s[1] + y) < WIN_H)
	{
		x = 0;
		while (x < s[2] && (s[0] + x) < WIN_W)
		{
			pos[0] = x;
			pos[1] = y;
			draw_screamer_pixel(hub, screamer, pos, s);
			x++;
		}
		y++;
	}
}

static void	update_timer_counter_2(t_hub *hub)
{
	if (hub->screamer_counter >= 20)
	{
		hub->show_screamer = 1;
		hub->screamer_index = (hub->screamer_index + 1) % 5;
		hub->screamer_counter = 0;
		hub->screamer_display_time = 0;
		hub->total_screamers++;
		if (hub->screamer_index == 3)
		{
			hub->timer_active = 0;
			hub->final_screamer_active = 1;
			return (stop_all_sounds(hub), play_end_sound(hub));
		}
	}
}

void	update_timer_counter(t_hub *hub, long long current_time,
		long long *last_time)
{
	int	track;

	hub->timer_seconds--;
	hub->screamer_counter++;
	if (hub->screamer_sound_played && hub->total_screamers >= 2)
	{
		track = ((hub->total_screamers - 2) % 3) + 1;
		play_ambiance_track(hub, track);
		hub->screamer_sound_played = 0;
	}
	update_timer_counter_2(hub);
	*last_time = current_time;
	if (hub->timer_seconds <= 0)
	{
		hub->timer_active = 0;
		hub->final_screamer_active = 1;
		return (stop_all_sounds(hub), play_end_sound(hub));
	}
}

void	render_timer_display(t_hub *hub)
{
	char	timer_str[10];
	int		i;
	int		x;
	int		y;

	if (!hub->door_broken)
		return ;
	snprintf(timer_str, sizeof(timer_str), "%d", hub->timer_seconds);
	x = WIN_W - 100;
	y = 30;
	i = 0;
	while (timer_str[i])
	{
		mlx_string_put(hub->mlx->mlx, hub->mlx->win, x + (i * 20), y,
			0xFF0000, &timer_str[i]);
		i++;
	}
}
