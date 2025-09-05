/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourchette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:14:39 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/05 15:42:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_one_fork(t_philo *p, int fork_id)
{
	pthread_mutex_lock(&p->env->forks[fork_id]);
	if (sim_stopped(p->env))
	{
		pthread_mutex_unlock(&p->env->forks[fork_id]);
		return (0);
	}
	log_state(p, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *p)
{
	int	a;
	int	b;

	a = p->left_fork;
	b = p->right_fork;
	if (a < b)
	{
		if (!lock_one_fork(p, a))
			return (0);
		if (!lock_one_fork(p, b))
			return (pthread_mutex_unlock(&p->env->forks[a]), 0);
	}
	else
	{
		if (!lock_one_fork(p, b))
			return (0);
		if (!lock_one_fork(p, a))
			return (pthread_mutex_unlock(&p->env->forks[b]), 0);
	}
	return (1);
}

int	init_forks(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->forks)
		return (1);
	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
	return (0);
}

void	release_forks(t_philo *p)
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

// // static void	take_forks(t_philo *p)
// // {
// // 	int	a;
// // 	int	b;

// // 	a = p->left_fork;
// // 	b = p->right_fork;
// // 	if (a < b)
// // 	{
// // 		pthread_mutex_lock(&p->env->forks[a]);
// // 		log_state(p, "has taken a fork");
// // 		pthread_mutex_lock(&p->env->forks[b]);
// // 		log_state(p, "has taken a fork");
// // 	}
// // 	else
// // 	{
// // 		pthread_mutex_lock(&p->env->forks[b]);
// // 		log_state(p, "has taken a fork");
// // 		pthread_mutex_lock(&p->env->forks[a]);
// // 		log_state(p, "has taken a fork");
// // 	}
// // }

// static int	take_forks(t_philo *p)
// {
// 	int	a = p->left_fork;
// 	int	b = p->right_fork;

// 	if (a < b)
// 	{
// 		pthread_mutex_lock(&p->env->forks[a]);
// 		if (sim_stopped(p->env))
// 			return (pthread_mutex_unlock(&p->env->forks[a]), 0);
// 		log_state(p, "has taken a fork");
// 		pthread_mutex_lock(&p->env->forks[b]);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&p->env->forks[b]);
// 		if (sim_stopped(p->env))
// 			return (pthread_mutex_unlock(&p->env->forks[b]), 0);
// 		log_state(p, "has taken a fork");
// 		pthread_mutex_lock(&p->env->forks[a]);
// 	}
// 	if (sim_stopped(p->env))
// 	{
// 		pthread_mutex_unlock(&p->env->forks[a]);
// 		pthread_mutex_unlock(&p->env->forks[b]);
// 		return (0);
// 	}
// 	log_state(p, "has taken a fork");
// 	return (1);
// }
