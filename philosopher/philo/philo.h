/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/05 15:32:17 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define PURPLE "\033[35m"
# define ORANGE "\033[38;5;208m"
# define GREEN "\033[32m"
# define BLUE "\033[38;5;117m"
# define WHITE "\033[97m"

typedef struct s_env
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_ms;
	int				stop_sim;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}					t_env;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	t_env			*env;
	pthread_mutex_t	meal_mutex;
	int				left_fork;
	int				right_fork;
}					t_philo;

int					init_env(t_env *env, int argc, char **argv);
t_philo				*init_philos(t_env *env);
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
long				now_ms(void);
long				since_start_ms(t_env *env);
void				msleep(long ms, t_env *env);
int					sim_stopped(t_env *env);
void				log_state(t_philo *p, const char *msg);
void				cleanup(t_env *env, t_philo *philos);
int					ft_strcmp(const char *s1, const char *s2);
void				*handle_one_philo(t_philo *p);

// fourchette.c
int					lock_one_fork(t_philo *p, int fork_id);
int					take_forks(t_philo *p);
int					init_forks(t_env *env);
void				release_forks(t_philo *p);

#endif
