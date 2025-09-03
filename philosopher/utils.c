/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:33:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/03 16:20:31 by clfouger         ###   ########.fr       */
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

void	log_state(t_philo *p, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&p->env->print_mutex);
	if (!p->env->stop_sim || msg[0] == 'd')
	{
		timestamp = now_ms() - p->env->start_ms;
		printf("%ld %d %s\n", timestamp, p->id, msg);
	}
	pthread_mutex_unlock(&p->env->print_mutex);
}
