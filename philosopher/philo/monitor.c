/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:26:46 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/06 14:39:50 by clfouger         ###   ########.fr       */
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
	long	last_meal;
	int		full;

	if (sim_stopped(p->env))
		return (0);
	pthread_mutex_lock(&p->meal_mutex);
	last_meal = p->last_meal;
	full = (p->env->max_meals != -1 && p->meals_eaten >= p->env->max_meals);
	pthread_mutex_unlock(&p->meal_mutex);
	if (full)
		return (0);
	if (now_ms() - last_meal > p->env->time_to_die)
	{
		pthread_mutex_lock(&p->env->stop_mutex);
		if (!p->env->stop_sim)
		{
			p->env->stop_sim = 1;
			pthread_mutex_unlock(&p->env->stop_mutex);
			log_state(p, "died");
			return (1);
		}
		pthread_mutex_unlock(&p->env->stop_mutex);
	}
	return (0);
}

static int	check_all_full(t_philo *philos, t_env *env)
{
	int	i;
	int	full;

	if (env->max_meals == -1)
		return (0);
	full = 0;
	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].meals_eaten >= env->max_meals)
			full++;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
		if (sim_stopped(env))
			return (0);
	}
	if (full == env->nb_philo)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_env	*env;
	int		i;

	philos = (t_philo *)arg;
	env = philos[0].env;
	while (!sim_stopped(env))
	{
		if (env->max_meals != -1 && check_all_full(philos, env))
		{
			stop_simulation(env);
			return (NULL);
		}
		i = 0;
		while (i < env->nb_philo && !sim_stopped(env))
		{
			if (check_death(&philos[i]))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
