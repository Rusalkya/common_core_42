/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:32:06 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/01 08:46:23 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

static void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->env->forks[p->left_fork]);
	log_state(p, "has taken a fork");
	pthread_mutex_lock(&p->env->forks[p->right_fork]);
	log_state(p, "has taken a fork");
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
	while (p->env->max_meals == -1 || p->meals_eaten < p->env->max_meals)
	{
		// prendre les fourchettes
		take_forks(p);
		// manger
		log_state(p, "is eating");
		p->last_meal = now_ms();
		p->meals_eaten++;
		msleep(p->env->time_to_eat);
		// reposer les fourchettes
		release_forks(p);
		// dormir
		log_state(p, "is sleeping");
		msleep(p->env->time_to_sleep);
		// penser
		log_state(p, "is thinking");
	}
	return (NULL);
}
