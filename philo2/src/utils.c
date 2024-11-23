/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:04:48 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/20 14:46:08 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	unequal_sleep(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(200);
	else
		usleep(0);
}

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
void	print_state_change(t_philo *philo, const char *state, long timestamp)
{
	// long	currtimestamp;

	// currtimestamp = get_timestamp_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	if (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
		printf("%ld %d %s\n", timestamp, philo->id + 1, state);
	else if (ft_strcmp(state, "died") == 0 && get_bool(&philo->mutex,
			&philo->dead))
		printf("%ld %d %s\n", timestamp, philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->print_lock);
}

/**
 * @brief Safe implementation of atoi to convert string to long
 *
 * This function converts a string to a long integer, checking for overflow.
 *
 * @param str The string to convert
 * @param result Pointer to store the result
 * @return int 1 if conversion was successful, 0 otherwise
 */
int	ft_atoi_safe(const char *str, long *result)
{
	long	n;
	int		sign;

	sign = 1;
	n = 0;
	if (!str)
		return (0);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		if (n > INT_MAX || n < INT_MIN)
			return (0);
		str++;
	}
	*result = (long)(n * sign);
	return (1);
}
