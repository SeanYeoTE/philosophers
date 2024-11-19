/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:54:07 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/11 19:57:52 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Simulate a philosopher eating
 * 
 * This function updates the philosopher's last meal time and meal count,
 * prints that the philosopher is eating, and then sleeps for the eating 
 * duration.
 * @param philo Pointer to the philosopher structure
 */
void	eat(t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp_in_ms() - philo->data->start_time;
	set_long(&philo->mutex, &philo->last_meal_time, timestamp);
	set_long(&philo->mutex, &philo->times_eaten, get_long(&philo->mutex,
			&philo->times_eaten) + 1);
	print_state_change(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	put_down_forks(philo, timestamp);
}

/**
 * @brief Simulate a philosopher sleeping
 * 
 * This function prints that the philosopher is sleeping and then sleeps
 * for the specified sleep duration.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	sleep_philo(t_philo *philo)
{
	print_state_change(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

/**
 * @brief Simulate a philosopher thinking
 * 
 * This function simply prints that the philosopher is thinking.
 * The actual thinking time is determined by the availability of forks.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	think(t_philo *philo)
{
	print_state_change(philo, "is thinking");
}
