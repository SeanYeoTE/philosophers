/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:36 by seayeo            #+#    #+#             */
/*   Updated: 2024/08/01 13:48:14 by seayeo           ###   ########.fr       */
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

typedef struct s_data t_data;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				id;
	long			time_last_used;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long			last_eat;
	bool			full;
	t_data			*data;
	pthread_mutex_t	*forks;
	
	// pthread_mutex_t	*print;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
}					t_philo;

typedef struct s_data
{
	long			num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	long			max_eat;
	bool			end_simulation;
	
	long			threads_running;
	pthread_mutex_t data_mutex;
	pthread_mutex_t write_mutex;
	pthread_t		monitor_thread;
	
	t_fork			*forks;
	t_philo			*philos;
	// pthread_mutex_t	print;
}					t_data;

# endif


// philo.c
void	write_error(char *str);
long	gettime(void);

// check_input.c
void	check_input(char **argv, t_data *data);

// init_data.c
void	init_data(t_data *data);

// safe_functions.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*func)(void *), void *arg, t_opcode opcode);

// helpers.c
bool	simulation_finished(t_data *data);
void    set_bool(pthread_mutex_t mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t mutex, bool *src);
void    set_long_nl(long *dest, long value);
void    set_long(pthread_mutex_t *mutex, long *dest, long value);
void    print_status(t_philo *philo, char *status);

// simulation.c
void	*mealtime(void *data);
void	simulation(t_data *data);