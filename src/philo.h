/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:48:16 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 13:12:28 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

#include <errno.h>

#ifndef PHILO_H
# define PHILO_H

#define DEBUG_MODE 1

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef struct s_table t_table;
typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}		t_fork;

typedef	struct s_philo
{
	int		id;
	long	meals_counter;
	bool	full;
	long	last_meal_time;
	t_table	*table;
	
	pthread_mutex_t	philo_mutex;
	
	t_fork	*first_fork;
	t_fork	*second_fork;
	pthread_t	thread;
}			t_philo;

typedef struct s_table
{
	long	num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_meals;
	bool	end_simulation;
	bool	all_threads_ready;
	long	threads_running_number;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t write_lock;
	pthread_t	monitor_thread;
	long	start_time;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

void	error_exit(const char *msg);
long	gettime(t_time_code timecode);
void	precise_usleep(long usec, t_table *table);

// utils.c
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

// input_check.c
void	input_check(t_table *table, char **argv);

// safe_functions.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handlle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// init.c
void	data_init(t_table	*table);

// simulation.c
void    thinking(t_philo *philo, bool pre_simulation);
void    dinner_start(t_table *table);
void    *dinner_simulation(void *data);

// synchro.c
void    wait_all_threads(t_table *table);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_num);
void	increase_long(pthread_mutex_t *mutex, long *target);

// write.c
void    write_status(t_philo_status status, t_philo *philo, bool debug);

// monitor.c
void    *monitor_dinner(void *data);

#endif