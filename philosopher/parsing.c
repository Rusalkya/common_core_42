/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:31:45 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/01 08:45:38 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_usage()
{
	fprintf(stderr,"error: entrer les arguments demandes\n");
	return (1);
}

static long	ato_l(const char *s)
{
	char	*end;
	long	v;

	v = strtol(s, &end, 10);
	if (*s == '\0' || *end != '\0' || v < 0)
	{
		fprintf(stderr, "invalid number: %s\n", s);
		exit(1);
	}
	return (v);
}

int	init_env(t_env *env, int argc, char **argv)
{
	int	i;

	env->nb_philo = (int)ato_l(argv[1]);
	env->time_to_die = ato_l(argv[2]);
	env->time_to_eat = ato_l(argv[3]);
	env->time_to_sleep = ato_l(argv[4]);
	if (argc >= 6)
		env->max_meals = (int)ato_l(argv[5]);
	else
		env->max_meals = -1;
	if (env->nb_philo <= 0)
	{
		fprintf(stderr, "nb_philo must be > 0\n");
		return (1);
	}
	pthread_mutex_init(&env->print_mutex, NULL);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (!env->forks)
		return (1);
	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
	env->start_ms = now_ms();
	return (0);
}

t_philo	*init_philos(t_env *env)
{
	t_philo	*philos;
	int		i;

	philos = calloc(env->nb_philo, sizeof(*philos));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < env->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].env = env;
		philos[i].last_meal = env->start_ms;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % env->nb_philo;
		i++;
	}
	return (philos);
}
