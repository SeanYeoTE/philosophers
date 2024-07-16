/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:48:16 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/16 14:14:39 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

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
	
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t	thread;
	t_table	*table;
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