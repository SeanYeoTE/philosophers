/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:05:13 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/11 20:36:44 by seayeo           ###   ########.fr       */
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

typedef struct s_data	t_data;

/**
 * @struct s_fork
 * @brief Represents a fork in the dining philosophers problem
 *
 * @var mutex Mutex for controlling access to the fork
 */
typedef struct s_fork
{
	long			last_used;
	pthread_mutex_t	mutex;
}	t_fork;

/**
 * @struct s_philo
 * @brief Represents a philosopher in the dining philosophers problem
 *
 * @var id Unique identifier for the philosopher
 * @var data Pointer to the shared data structure
 * @var times_eaten Number of times the philosopher has eaten
 * @var last_meal_time Timestamp of the philosopher's last meal
 * @var full Boolean indicating if the philosopher is full
 * @var dead Boolean indicating if the philosopher has died
 * @var thread Thread handle for the philosopher
 * @var mutex Mutex for controlling access to the philosopher's data
 */
typedef struct s_philo
{
	int				id;
	t_data			*data;
	long			times_eaten;
	long			last_meal_time;
	bool			full;
	bool			dead;
	pthread_t		thread;
	pthread_mutex_t	mutex;
}	t_philo;

/**
 * @struct s_data
 * @brief Contains shared data for the dining philosophers simulation
 *
 * @var forks Array of forks
 * @var start_mutex Mutex for controlling the start of the simulation
 * @var num_philosophers Number of philosophers
 * @var time_to_die Time limit for a philosopher to eat before dying
 * @var time_to_eat Time it takes for a philosopher to eat
 * @var time_to_sleep Time a philosopher spends sleeping
 * @var max_meals Maximum number of meals before the simulation ends (optional)
 * @var end_simulation Flag to indicate the end of the simulation
 * @var start_time Timestamp when the simulation started
 * @var ready_count Counter for philosophers ready to start
 * @var start_flag Flag to indicate the start of the simulation
 * @var monitor_thread Thread handle for the monitoring thread
 * @var philosophers Array of philosopher structures
 */
typedef struct s_data
{
	t_fork			*forks;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	print_lock;
	long			num_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	bool			end_simulation;
	long			start_time;
	long			ready_count;
	bool			start_flag;
	pthread_t		monitor_thread;
	t_philo			*philosophers;
}	t_data;

void	initialize_forks(t_data *data);
void	create_philosopher_threads(t_data *data);
void	join_philosopher_threads(t_data *data);
void	destroy_mutexes(t_data *data);

// thread_creation.c
int		thread_creation(pthread_t *thread,
			void *(*start_routine)(void *), void *arg);
// forks_status.c
void	pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo, long timestamp);
bool	hungriest_philosopher(t_data *data, int current_id);

// philo_status.c
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

// utils.c
int		ft_strcmp(const char *s1, const char *s2);
void	unequal_sleep(t_philo *philo);
long	get_timestamp_in_ms(void);
void	print_state_change(t_philo *philo, const char *state);
int		ft_atoi_safe(const char *str, long *result);

// simulation.c
void	*single_philo(void *arg);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

// getandset.c
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_bool(pthread_mutex_t *mutex, bool *value, bool new_value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *value, long new_value);

#endif
