/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screamer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/time.h>

static void	init_door_broken(t_hub *hub)
{
	hub->door_broken = 1;
	hub->timer_active = 1;
	hub->timer_seconds = 100;
	hub->screamer_counter = 0;
	hub->show_screamer = 1;
	hub->screamer_index = 0;
	hub->screamer_display_time = 0;
	hub->total_screamers = 1;
	hub->screamer_sound_played = 0;
	if (!hub->ambiance_started)
	{
		play_music_sound(hub);
		hub->ambiance_started = 1;
	}
}

static void	check_door_passage(t_hub *hub)
{
	int	player_x;
	int	player_y;

	if (hub->door_broken)
		return ;
	player_x = (int)hub->player->posx;
	player_y = (int)hub->player->posy;
	if (player_y >= 0 && player_x >= 0 && hub->map[player_y]
		&& hub->map[player_y][player_x])
	{
		if (hub->map[player_y][player_x] == '5')
			init_door_broken(hub);
	}
}

void	update_timer(t_hub *hub)
{
	static long long	last_time = 0;
	struct timeval		tv;
	long long			current_time;

	check_door_passage(hub);
	if (!hub->timer_active)
		return ;
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (last_time == 0)
		last_time = current_time;
	if (hub->show_screamer)
		update_screamer_display(hub, current_time, &last_time);
	else if (current_time - last_time >= 1000)
		update_timer_counter(hub, current_time, &last_time);
}

void	render_screamer(t_hub *hub)
{
	t_img	*screamer;
	int		s[4];
	int		screamer_idx;

	if (!hub->show_screamer && !hub->final_screamer_active)
		return ;
	if (hub->final_screamer_active)
		screamer_idx = 3 + hub->final_screamer_frame;
	else
		screamer_idx = hub->screamer_index;
	screamer = hub->mlx->screamers[screamer_idx];
	if (!screamer || !screamer->ptr)
		return ;
	s[2] = screamer->w * 3.5;
	s[3] = screamer->h * 3.5;
	s[0] = (WIN_W - s[2]) / 2;
	s[1] = (WIN_H - s[3]) / 2 + 150;
	render_screamer_loop(hub, screamer, s);
}

void	render_red_filter(t_hub *hub)
{
	int	time_elapsed;

	if (!hub->door_broken)
		return ;
	time_elapsed = 100 - hub->timer_seconds;
	render_red_filter_loop(hub, time_elapsed);
}
