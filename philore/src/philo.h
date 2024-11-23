/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:42:52 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 23:56:06 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_fork
{
	long			id;
	long			last_used;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	long			id;
	long			meals;
	long			last_meal;
	bool			full;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	mutex;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_meals;
	long			start_time;
	bool			start_flag;
	bool			dead;
	bool			end_sim;
	t_fork			*forks;
	pthread_t		monitor_thread;
	pthread_mutex_t	table_data;
	pthread_mutex_t	print;
	t_philo			*philos;
}					t_table;


int					check_args(int argc, char **argv, t_table *table);

// init.c
int					init_forks(t_table *table);
int					init_threads(t_table *table);
int					assign_forks(t_table *table);
int					init_others(t_table *table);

// utils.c
void				spinlock(bool *start_flag, pthread_mutex_t *table_data);
void				errormsg(char *s);
int					ft_atol_assign(const char *str, long *num);
int					thread_creation(pthread_t *thread,
						void *(*start_routine)(void *), void *arg);

// utils2.c
void				desync_start(long id);
void				precise_sleep(t_philo *philo, long time, long prev_timestamp);
void				print_state_change(t_philo *philo, char *state, long timestamp);
		
// getandset.c
long				get_time(int type);
bool				get_bool(pthread_mutex_t *mutex, bool *value);
void				set_bool(pthread_mutex_t *mutex, bool *value, bool new_value);
long				get_long(pthread_mutex_t *mutex, long *value);
void				set_long(pthread_mutex_t *mutex, long *value, long new_value);

// process.c
void				*philo_life(void *arg);
void				*solo(void *arg);
int					is_philo_dead(t_philo *philo);
void				*monitor(void *arg);

// philo_status.c
void				pick_fork(t_philo *philo);
void				philo_eat(t_philo *philo, long prev_timestamp);
void				put_down_forks(t_philo *philo, long prev_timestamp);
void				philo_sleep(t_philo *philo, long prev_timestamp);
void				philo_think(t_philo *philo, long prev_timestamp);

#endif
