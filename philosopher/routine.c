/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:32:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:20 by clfouger         ###   ########.fr       */
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

void msleep(long ms, t_env *env)
{
    long start = now_ms();
    while (!sim_stopped(env))
    {
        long elapsed = now_ms() - start;
        if (elapsed >= ms)
            break;
        usleep(200);
    }
}

static void take_forks(t_philo *p)
{
	int a = p->left_fork;
	int b = p->right_fork;

	if (a < b)
	{
		pthread_mutex_lock(&p->env->forks[a]);
		log_state(p, "has taken a fork");
		pthread_mutex_lock(&p->env->forks[b]);
		log_state(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&p->env->forks[b]);
		log_state(p, "has taken a fork");
		pthread_mutex_lock(&p->env->forks[a]);
		log_state(p, "has taken a fork");
	}
}

static void release_forks(t_philo *p)
{
	int a = p->left_fork;
	int b = p->right_fork;

	if (a < b)
	{
		pthread_mutex_unlock(&p->env->forks[b]);
		pthread_mutex_unlock(&p->env->forks[a]);
	}
	else
	{
		pthread_mutex_unlock(&p->env->forks[a]);
		pthread_mutex_unlock(&p->env->forks[b]);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(2000); /* petit décalage de départ */

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

		msleep(p->env->time_to_eat, p->env);
		release_forks(p);

		if (sim_stopped(p->env))
			break ;
		log_state(p, "is sleeping");
		msleep(p->env->time_to_sleep, p->env);

		if (sim_stopped(p->env))
			break ;
		log_state(p, "is thinking");
	}
	return (NULL);
}
