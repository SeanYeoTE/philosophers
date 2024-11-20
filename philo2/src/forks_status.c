/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:53:01 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/20 14:53:03 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Simulate a philosopher picking up forks
 * 
 * This function implements the "even-odd" fork picking strategy to avoid
 * deadlocks.
 * Even-numbered philosophers pick up their right fork first, while odd-numbered
 * philosophers pick up their left fork first.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	pick_up_forks(t_philo *philo)
{
	int		left_fork;
	int		right_fork;
	long	timestamp;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philos;
	timestamp = get_timestamp_in_ms() - philo->data->start_time;
	// if (philo->id % 2 == 0)
	// {
	pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
	print_state_change(philo, "has taken a fork", timestamp);
	pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
	print_state_change(philo, "has taken a fork", timestamp);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
	// 	print_state_change(philo, "has taken a fork", timestamp);
	// 	pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
	// 	print_state_change(philo, "has taken a fork", timestamp);
	// }
	eat(philo, timestamp);
}

/**
 * @brief Simulate a philosopher putting down forks
 * 
 * This function releases the mutexes for both forks.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	put_down_forks(t_philo *philo, long timestamp)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philos;
	philo->data->forks[left_fork].last_used = timestamp;
	philo->data->forks[right_fork].last_used = timestamp;
	pthread_mutex_unlock(&philo->data->forks[right_fork].mutex);
	pthread_mutex_unlock(&philo->data->forks[left_fork].mutex);
}

/**
 * @brief Determine the hungriest philosopher among the current philosopher 
 * and its two neighbors
 * 
 * This function compares the current philosopher with its left and right
 * neighbors to determine if itself has waited the longest since their 
 * last meal.
 * 
 * @param data Pointer to the shared data structure
 * @param current_id The ID of the current philosopher
 * @return bool true if the current philosopher is the hungriest, false otherwise
 */
bool	hungriest_philosopher(t_data *data, int current_id)
{
	int		left_fork;
	int		right_fork;
	long	times[3];

	left_fork = current_id;
	right_fork = (current_id + 1) % data->num_philos;
	times[0] = get_long(&data->philos[current_id].mutex,
			&data->philos[current_id].last_meal_time);
	times[1] = get_long(&data->forks[left_fork].mutex,
			&data->forks[left_fork].last_used);
	times[2] = get_long(&data->forks[right_fork].mutex,
			&data->forks[right_fork].last_used);
	if (times[1] != times[0] && times[2] != times[0])
		return (true);
	return (false);
}
