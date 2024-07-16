/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:48:16 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/16 21:41:06 by seayeo           ###   ########.fr       */
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
	
	t_fork	*left_fork;
	t_fork	*right_fork;
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
	long	start_time;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

void	error_exit(const char *msg);

// input_check.c
void	input_check(t_table *table, char **argv);

// safe_functions.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handlle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// init.c

#endif