/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:33:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/06 14:46:23 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	since_start_ms(t_env *env)
{
	return (now_ms() - env->start_ms);
}

void	msleep(long ms, t_env *env)
{
	long	start;

	start = now_ms();
	while (!sim_stopped(env))
	{
		if (now_ms() - start >= ms)
			break ;
		usleep(100);
	}
}

int	sim_stopped(t_env *env)
{
	int	stopped;

	pthread_mutex_lock(&env->stop_mutex);
	stopped = env->stop_sim;
	pthread_mutex_unlock(&env->stop_mutex);
	return (stopped);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
