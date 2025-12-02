/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_music.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:27:13 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/wait.h>
#include <signal.h>

void	play_music_sound(t_hub *hub)
{
	char	path[256];

	snprintf(path, sizeof(path), "sounds/music.wav");
	if (access(path, F_OK) != 0)
		return ;
	hub->music_pid = fork();
	if (hub->music_pid == 0)
	{
		setpgid(0, 0);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		execlp("aplay", "aplay", "-q", path, NULL);
		execlp("paplay", "paplay", path, NULL);
		execlp("ffplay", "ffplay", "-nodisp", "-autoexit",
			"-loglevel", "quiet", path, NULL);
		exit(0);
	}
}

void	play_ambiance_track(t_hub *hub, int track_num)
{
	char	path[256];

	if (track_num < 1 || track_num > 3)
		return ;
	snprintf(path, sizeof(path), "sounds/ambiance%d.wav", track_num);
	if (access(path, F_OK) != 0)
		return ;
	hub->ambiance_pid = fork();
	if (hub->ambiance_pid == 0)
	{
		setpgid(0, 0);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		execlp("aplay", "aplay", "-q", path, NULL);
		execlp("paplay", "paplay", path, NULL);
		execlp("ffplay", "ffplay", "-nodisp", "-autoexit",
			"-loglevel", "quiet", path, NULL);
		exit(0);
	}
}
