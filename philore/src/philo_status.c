/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:14:21 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 23:13:48 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	pick_fork(t_philo *philo)
{
	long	time;

	time = get_time(1) - philo->table->start_time;
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_state_change(philo, "has taken a fork", time);
	print_state_change(philo, "has taken a fork", time);
	philo->left_fork->last_used = time;
	philo->right_fork->last_used = time;	
	philo_eat(philo, time);
}

void	philo_eat(t_philo *philo, long prev_timestamp)
{
	set_long(&philo->mutex, &philo->last_meal, prev_timestamp);
	set_long(&philo->mutex, &philo->meals, get_long(&philo->mutex,
			&philo->meals) + 1);
	if (get_long(&philo->mutex, &philo->meals) == philo->table->num_meals)
		set_bool(&philo->mutex, &philo->full, true);
	print_state_change(philo, "is eating", prev_timestamp);
	precise_sleep(philo, philo->table->time_to_eat, prev_timestamp);
	put_down_forks(philo, get_time(1) - philo->table->start_time);
}

void	put_down_forks(t_philo *philo, long prev_timestamp)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo_sleep(philo, prev_timestamp);
}

void	philo_sleep(t_philo *philo, long prev_timestamp)
{
	print_state_change(philo, "is sleeping", prev_timestamp);
	precise_sleep(philo, philo->table->time_to_sleep, prev_timestamp);
	philo_think(philo, get_time(1) - philo->table->start_time);
}

void	philo_think(t_philo *philo, long prev_timestamp)
{
	print_state_change(philo, "is thinking", prev_timestamp);
}