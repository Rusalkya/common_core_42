/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:26:46 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/01 13:51:17 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_simulation(t_env *env)
{
	pthread_mutex_lock(&env->stop_mutex);
	env->stop_sim = 1;
	pthread_mutex_unlock(&env->stop_mutex);
}

static int	check_death(t_philo *p)
{
	if (now_ms() - p->last_meal > p->env->time_to_die)
	{
		log_state(p, "died");
		stop_simulation(p->env);
		return (1);
	}
	return (0);
}
void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_env	*env;
	int		i;

	philos = (t_philo *)arg;
	env = philos[0].env;
	while (1)
	{
		i = 0;
		while (i < env->nb_philo)
		{
			if (check_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (env->stop_sim)
			return (NULL);
		usleep(1000);
	}
}
