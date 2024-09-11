/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:54:07 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/11 13:35:31 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current timestamp in milliseconds
 * 
 * This function uses gettimeofday to get the current time and converts it
 * to milliseconds since the Epoch.
 * 
 * @return long The current timestamp in milliseconds
 */
long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Print a state change for a philosopher
 * 
 * This function prints the current timestamp, philosopher ID, and the new state.
 * 
 * @param philo Pointer to the philosopher structure
 * @param state String describing the new state
 */
void	print_state_change(t_philo *philo, const char *state)
{
	long	timestamp;

	timestamp = get_timestamp_in_ms() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id + 1, state);
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
 * @brief Simulate a philosopher picking up forks
 * 
 * This function implements the "even-odd" fork picking strategy to avoid deadlocks.
 * Even-numbered philosophers pick up their right fork first, while odd-numbered
 * philosophers pick up their left fork first.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	pick_up_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philosophers;
	if (philo->id % 2 == 0) {
		pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
		print_state_change(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
		print_state_change(philo, "has taken a fork");
	} else {
		pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
		print_state_change(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
		print_state_change(philo, "has taken a fork");
	}
}

/**
 * @brief Simulate a philosopher putting down forks
 * 
 * This function releases the mutexes for both forks.
 * 
 * @param philo Pointer to the philosopher structure
 */
void put_down_forks(t_philo *philo)
{
	int left_fork;
	int right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philosophers;
	pthread_mutex_unlock(&philo->data->forks[right_fork].mutex);
	pthread_mutex_unlock(&philo->data->forks[left_fork].mutex);
}

/**
 * @brief Determine the hungriest philosopher among the current philosopher and its two neighbors
 * 
 * This function compares the current philosopher with its left and right neighbors
 * to determine if itself has waited the longest since their last meal.
 * 
 * @param data Pointer to the shared data structure
 * @param current_id The ID of the current philosopher
 * @return bool true if the current philosopher is the hungriest, false otherwise
 */
bool	hungriest_philosopher(t_data *data, int current_id)
{
    int left_id = (current_id - 1 + data->num_philosophers) % data->num_philosophers;
    int right_id = (current_id + 1) % data->num_philosophers;
    long current_time = get_timestamp_in_ms();
    long wait_times[3];

    pthread_mutex_lock(&data->philosophers[current_id].mutex);
    wait_times[0] = current_time - data->philosophers[current_id].last_meal_time;
    pthread_mutex_unlock(&data->philosophers[current_id].mutex);

    pthread_mutex_lock(&data->philosophers[left_id].mutex);
    wait_times[1] = current_time - data->philosophers[left_id].last_meal_time;
    pthread_mutex_unlock(&data->philosophers[left_id].mutex);

    pthread_mutex_lock(&data->philosophers[right_id].mutex);
    wait_times[2] = current_time - data->philosophers[right_id].last_meal_time;
    pthread_mutex_unlock(&data->philosophers[right_id].mutex);

    if (wait_times[1] > wait_times[0] && wait_times[2] > wait_times[0])
        return (false);
    return (true);
}