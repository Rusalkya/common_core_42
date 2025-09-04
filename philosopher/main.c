/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:09:57 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/04 11:46:49 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_usage(char *prog)
{
	printf("usage: %s nb_philo time_die time_eat time_sleep [max_meals]\n",
		prog);
	return (1);
}

static int	start_philos(t_env *env, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	init_and_start(t_env *env, t_philo **philos, int argc, char **argv)
{
	int	i;

	if (init_env(env, argc, argv) != 0)
		return (1);
	*philos = init_philos(env);
	if (!*philos)
		return (1);
	env->start_ms = now_ms();
	i = 0;
	while (i < env->nb_philo)
	{
		(*philos)[i].last_meal = env->start_ms;
		i++;
	}
	if (start_philos(env, *philos))
		return (free(*philos), 1);
	return (0);
}

static void	join_threads(t_env *env, t_philo *philos, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < env->nb_philo)
		pthread_join(philos[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philos;
	pthread_t	monitor;

	if (argc < 5)
		return (error_usage(argv[0]));
	if (init_and_start(&env, &philos, argc, argv) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (free(philos), 1);
	join_threads(&env, philos, monitor);
	free(philos);
	free(env.forks);
	return (0);
}
