/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:54:07 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/08 22:16:54 by seayeo           ###   ########.fr       */
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
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
	pthread_mutex_lock(&philo->data->print_lock);
	if (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
		printf("%ld %d %s\n", timestamp, philo->id + 1, state);
	else if (ft_strcmp(state, "died") == 0 && get_bool(&philo->mutex,
			&philo->dead))
		printf("%ld %d %s\n", timestamp, philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->print_lock);
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
	put_down_forks(philo, timestamp);
}
