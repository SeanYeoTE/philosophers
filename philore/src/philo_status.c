/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:14:21 by seayeo            #+#    #+#             */
/*   Updated: 2024/12/06 16:17:10 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	pick_fork(t_philo *philo, long prev_timestamp)
{
	long	printed_time;
	
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	prev_timestamp = get_time(1);
	printed_time = prev_timestamp - philo->table->start_time;
	print_state_change(philo, "has taken a fork", printed_time);
	print_state_change(philo, "has taken a fork", printed_time);
	philo->left_fork->last_used = prev_timestamp;
	philo->right_fork->last_used = prev_timestamp;
	philo_eat(philo, prev_timestamp);
}

void	philo_eat(t_philo *philo, long prev_timestamp)
{
	long	printed_time;

	printed_time = prev_timestamp - philo->table->start_time;
	set_long(&philo->mutex, &philo->last_meal, prev_timestamp);
	set_long(&philo->mutex, &philo->meals, get_long(&philo->mutex,
			&philo->meals) + 1);
	if (get_long(&philo->mutex, &philo->meals) == philo->table->num_meals
			&&	philo->table->num_meals > 0)
		set_bool(&philo->mutex, &philo->full, true);
	print_state_change(philo, "is eating", printed_time);
	precise_sleep(philo, philo->table->time_to_eat, prev_timestamp);
	put_down_forks(philo, get_time(1));
}

void	put_down_forks(t_philo *philo, long prev_timestamp)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo_sleep(philo, prev_timestamp);
}

void	philo_sleep(t_philo *philo, long prev_timestamp)
{
	long	printed_time;

	printed_time = prev_timestamp - philo->table->start_time;
	print_state_change(philo, "is sleeping", printed_time);
	precise_sleep(philo, philo->table->time_to_sleep, prev_timestamp);
	if (get_bool(&philo->mutex, &philo->full))
		return ;
	philo_think(philo, get_time(1));
}

void	philo_think(t_philo *philo, long prev_timestamp)
{
	long	printed_time;

	printed_time = prev_timestamp - philo->table->start_time;
	print_state_change(philo, "is thinking", printed_time);
}