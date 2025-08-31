/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:33:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/26 10:06:54 by clfouger         ###   ########.fr       */
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

void	msleep(long ms)
{
	if (ms <= 0)
		return ;
	usleep(ms * 1000);
}

void	log_state(t_philo *p, const char *msg)
{
	pthread_mutex_lock(&p->env->print_mutex);
	printf("%ld %d %s\n", since_start_ms(p->env), p->id, msg);
	pthread_mutex_unlock(&p->env->print_mutex);
}
