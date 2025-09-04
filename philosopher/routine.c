/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:32:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/03 17:07:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *p)
{
	int	a;
	int	b;

	a = p->left_fork;
	b = p->right_fork;
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

static void	release_forks(t_philo *p)
{
	int	a;
	int	b;

	a = p->left_fork;
	b = p->right_fork;
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

static void	start_eating(t_philo *p)
{
	log_state(p, "is eating");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = now_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	msleep(p->env->time_to_eat, p->env);
	release_forks(p);
}

static void	start_sleeping(t_philo *p)
{
	if (sim_stopped(p->env))
		return ;
	log_state(p, "is sleeping");
	msleep(p->env->time_to_sleep, p->env);
	if (!sim_stopped(p->env))
		log_state(p, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(2000);
	while (!sim_stopped(p->env) && (p->env->max_meals == -1
			|| p->meals_eaten < p->env->max_meals))
	{
		take_forks(p);
		if (sim_stopped(p->env))
		{
			release_forks(p);
			break ;
		}
		start_eating(p);
		if (sim_stopped(p->env))
			break ;
		start_sleeping(p);
	}
	return (NULL);
}
