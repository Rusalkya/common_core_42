/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:21:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 12:40:11 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/wait.h>
#include <signal.h>

static void	stop_music_pid(t_hub *hub)
{
	if (hub->music_pid > 0)
	{
		kill(-hub->music_pid, SIGKILL);
		kill(hub->music_pid, SIGKILL);
		waitpid(hub->music_pid, NULL, WNOHANG);
	}
	system("killall -9 aplay paplay ffplay 2>/dev/null");
	usleep(100000);
	system("killall -9 aplay paplay ffplay 2>/dev/null");
}

void	stop_all_sounds(t_hub *hub)
{
	if (hub->footstep_pid > 0)
	{
		kill(hub->footstep_pid, SIGKILL);
		waitpid(hub->footstep_pid, NULL, WNOHANG);
	}
	if (hub->ambiance_pid > 0)
	{
		kill(-hub->ambiance_pid, SIGKILL);
		kill(hub->ambiance_pid, SIGKILL);
		waitpid(hub->ambiance_pid, NULL, WNOHANG);
	}
	stop_music_pid(hub);
}

void	stop_footstep_sound(t_hub *hub)
{
	if (hub->footstep_pid > 0)
	{
		kill(hub->footstep_pid, SIGTERM);
		waitpid(hub->footstep_pid, NULL, WNOHANG);
		hub->footstep_pid = -1;
	}
}

void	play_sound(char *sound_file)
{
	pid_t	pid;
	char	path[256];

	if (!sound_file)
		return ;
	snprintf(path, sizeof(path), "sounds/%s", sound_file);
	if (access(path, F_OK) != 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		execlp("aplay", "aplay", "-q", path, NULL);
		execlp("paplay", "paplay", path, NULL);
		execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet",
			path, NULL);
		exit(0);
	}
}

void	play_end_sound(t_hub *hub)
{
	char	path[256];

	snprintf(path, sizeof(path), "sounds/end.wav");
	if (access(path, F_OK) != 0)
		return ;
	hub->end_sound_pid = fork();
	if (hub->end_sound_pid == 0)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		execlp("aplay", "aplay", "-q", path, NULL);
		execlp("paplay", "paplay", path, NULL);
		execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet",
			path, NULL);
		exit(0);
	}
}
