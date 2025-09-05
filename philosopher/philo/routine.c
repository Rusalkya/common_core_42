/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:32:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/05 15:35:11 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_one_philo(t_philo *p)
{
	log_state(p, "has taken a fork");
	while (!sim_stopped(p->env))
		usleep(1000);
	return (NULL);
}

static void	philo_eat(t_philo *p)
{
	log_state(p, "is eating");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = now_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	msleep(p->env->time_to_eat, p->env);
	release_forks(p);
}

static void	philo_rest(t_philo *p)
{
	log_state(p, "is sleeping");
	msleep(p->env->time_to_sleep, p->env);
	if (!sim_stopped(p->env))
		log_state(p, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->env->nb_philo == 1)
		return (handle_one_philo(p));
	if (p->id % 2 == 0)
		usleep(2000);
	while (!sim_stopped(p->env) && (p->env->max_meals == -1
			|| p->meals_eaten < p->env->max_meals))
	{
		take_forks(p);
		if (sim_stopped(p->env))
			break ;
		philo_eat(p);
		if (sim_stopped(p->env))
			break ;
		philo_rest(p);
	}
	return (NULL);
}
