/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:41:59 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/06 14:46:27 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_all(t_env *env, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->print_mutex);
	pthread_mutex_destroy(&env->stop_mutex);
	free(philos);
	free(env->forks);
}

void	cleanup(t_env *env, t_philo *philos)
{
	pthread_mutex_destroy(&env->print_mutex);
	free(philos);
}
