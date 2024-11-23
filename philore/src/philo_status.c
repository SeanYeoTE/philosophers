/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:14:21 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 21:56:51 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	pick_fork(t_philo *philo)
{
	long	time;

	time = get_time(1) - philo->table->start_time;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	set_long(&philo->table->forks[philo->id].last_used, time);
	philo_eat(philo, time);
}

void	philo_eat(t_philo *philo, long prev_timestamp)
{
	long	timestamp;

	timestamp = get_time(1) - philo->table->start_time;
	set_long(&philo->mutex, &philo->last_meal_time, timestamp);
	set_long(&philo->mutex, &philo->times_eaten, get_long(&philo->mutex,
			&philo->times_eaten) + 1);
	precise_sleep(philo->table->time_to_eat, timestamp, prev_timestamp);
	put_down_forks(philo, prev_timestamp);
}

void	put_down_forks(t_philo *philo, long prev_timestamp)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_sleep(philo, prev_timestamp);
}

void	philo_sleep(t_philo, long prev_timestamp)
{
	long	timestamp;

	timestamp = get_time(1) - philo->table->start_time;
	precise_sleep(philo->table->time_to_sleep, timestamp, prev_timestamp);
	timestamp = get_time(1) - philo->table->start_time;
	philo_think(philo, timestamp);
}

void	philo_think(t_philo *philo, long prev_timestamp)
{
	print_state_change(philo, "is thinking", prev_timestamp);
}