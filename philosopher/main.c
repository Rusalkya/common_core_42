/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:09:57 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/31 14:02:45 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env	env;
	t_philo	*philos;
	int		i;

	if (argc < 5)
		return (error_usage(argv[0]));
	if (init_env(&env, argc, argv) != 0)
		return (1);
	philos = init_philos(&env);
	if (!philos)
		return (1);
	i = 0;
	while (i < env.nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (free(philos), 1);
		i++;
	}
	i = 0;
	while (i < env.nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
