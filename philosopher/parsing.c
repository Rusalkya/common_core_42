/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:31:45 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/05 16:57:48 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	log_state(t_philo *p, const char *state)
{
	long	timestamp;

	pthread_mutex_lock(&p->env->print_mutex);
	if (!sim_stopped(p->env))
	{
		timestamp = now_ms() - p->env->start_ms;
		if (!ft_strcmp(state, "has taken a fork"))
			printf("%ld %d %s🍴 %s%s\n", timestamp, p->id, PURPLE, state, RESET);
		else if (!ft_strcmp(state, "is eating"))
			printf("%ld %d %s😋 %s%s\n", timestamp, p->id, ORANGE, state, RESET);
		else if (!ft_strcmp(state, "is sleeping"))
			printf("%ld %d %s💤 %s%s\n", timestamp, p->id, GREEN, state, RESET);
		else if (!ft_strcmp(state, "is thinking"))
			printf("%ld %d %s🧠 %s%s\n", timestamp, p->id, BLUE, state, RESET);
		else if (!ft_strcmp(state, "died"))
			printf("%ld %d %s💀 %s%s\n", timestamp, p->id, WHITE, state, RESET);
	}
	pthread_mutex_unlock(&p->env->print_mutex);
}

static long	ato_l(const char *s)
{
	char	*end;
	long	v;

	v = strtol(s, &end, 10);
	if (*s == '\0' || *end != '\0' || v < 0)
	{
		fprintf(stderr, "Invalid number: %s\n", s);
		exit(1);
	}
	return (v);
}

int	init_env(t_env *env, int argc, char **argv)
{
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
	pthread_mutex_init(&env->stop_mutex, NULL);
	if (init_forks(env))
		return (1);
	env->stop_sim = 0;
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
		philos[i].meals_eaten = 0;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % env->nb_philo;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	return (philos);
}
