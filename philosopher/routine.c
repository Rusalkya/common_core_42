/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:32:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/03 10:49:49 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sim_stopped(t_env *env)
{
	int	stopped;

	pthread_mutex_lock(&env->stop_mutex);
	stopped = env->stop_sim;
	pthread_mutex_unlock(&env->stop_mutex);
	return (stopped);
}

static void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->env->forks[p->right_fork]);
		log_state(p, "has taken a fork");
		pthread_mutex_lock(&p->env->forks[p->left_fork]);
		log_state(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&p->env->forks[p->left_fork]);
		log_state(p, "has taken a fork");
		pthread_mutex_lock(&p->env->forks[p->right_fork]);
		log_state(p, "has taken a fork");
	}
}

static void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->env->forks[p->left_fork]);
	pthread_mutex_unlock(&p->env->forks[p->right_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(5000);
	while (!sim_stopped(p->env)
		&& (p->env->max_meals == -1 || p->meals_eaten < p->env->max_meals))
	{
		take_forks(p);
		if (sim_stopped(p->env))
			break ;
		log_state(p, "is eating");
		pthread_mutex_lock(&p->meal_mutex);
		p->last_meal = now_ms();
		p->meals_eaten++;
		pthread_mutex_unlock(&p->meal_mutex);
		msleep(p->env->time_to_eat);
		release_forks(p);
		if (sim_stopped(p->env))
			break ;
		log_state(p, "is sleeping");
		msleep(p->env->time_to_sleep);
		if (sim_stopped(p->env))
			break ;
		log_state(p, "is thinking");
	}
	return (NULL);
}
