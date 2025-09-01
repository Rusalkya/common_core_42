/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/01 08:48:21 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_env
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_ms;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t *forks;
}	t_env;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal;
	int			meals_eaten;
	t_env		*env;
	int			left_fork;
	int			right_fork;
}	t_philo;

/* parsing.c */
int		error_usage(char *prog);
int		init_env(t_env *env, int argc, char **argv);
t_philo	*init_philos(t_env *env);

/* routine.c */
void	*philo_routine(void *arg);

/* utils.c */
long	now_ms(void);
long	since_start_ms(t_env *env);
void	msleep(long ms);
void	log_state(t_philo *p, const char *msg);

/* clean.c */
void	cleanup(t_env *env, t_philo *philos);

#endif
