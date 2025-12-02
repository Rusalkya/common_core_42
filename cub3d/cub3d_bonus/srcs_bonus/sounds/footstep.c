/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   footstep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:40:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:26:55 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/wait.h>
#include <signal.h>

static void	fork_footstep_sound(t_hub *hub, char *path)
{
	hub->footstep_pid = fork();
	if (hub->footstep_pid == 0)
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

void	play_footstep_sound(t_hub *hub)
{
	static long long	last_time = 0;
	struct timeval		tv;
	long long			current_time;
	char				path[256];
	int					delay;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	delay = 400;
	if (hub->key->ctrl)
		delay = 333;
	if (current_time - last_time < delay)
		return ;
	last_time = current_time;
	stop_footstep_sound(hub);
	snprintf(path, sizeof(path), "sounds/footstep.wav");
	if (access(path, F_OK) != 0)
		return ;
	fork_footstep_sound(hub, path);
}
