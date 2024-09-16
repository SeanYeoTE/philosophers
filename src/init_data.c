/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/16 17:51:08 by seayeo           ###   ########.fr       */
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
 * @brief Initialize forks for the simulation
 *
 * This function allocates memory for forks and initializes their mutexes.
 *
 * @param data Pointer to the shared data structure
 */
void	initialize_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->num_philosophers * sizeof(t_fork));
	if (!data->forks)
		error_exit("Failed to allocate memory for forks");
	i = 0;
	while (i < data->num_philosophers)
	{
		data->forks[i].last_used = 0;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
}

/**
 * @brief Create threads for each philosopher
 *
 * This function initializes philosopher structures and creates threads 
 * for each philosopher.
 *
 * @param data Pointer to the shared data structure
 */
void	create_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->num_philosophers)
	{
		philo = &data->philosophers[i];
		philo->id = i;
		philo->last_meal_time = get_timestamp_in_ms();
		philo->data = data;
		philo->times_eaten = 0;
		philo->full = false;
		philo->dead = false;
		pthread_mutex_init(&data->philosophers[i].mutex, NULL);
		if (data->num_philosophers == 1)
			if (pthread_create(&philo->thread, NULL, single_philo, philo) != 0)
				error_exit("Failed to create philosopher thread");
		else
			if (pthread_create(&philo->thread, NULL, philo_routine, philo) != 0)
				error_exit("Failed to create philosopher thread");
	}
	set_long(&data->start_mutex, &data->start_time, get_timestamp_in_ms());
	set_bool(&data->start_mutex, &data->start_flag, true);
}

/**
 * @brief Join all philosopher threads
 *
 * This function waits for all philosopher threads to complete.
 *
 * @param data Pointer to the shared data structure
 */
void	join_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

/**
 * @brief Destroy all mutexes and free allocated memory
 *
 * This function cleans up resources by destroying mutexes and 
 * freeing allocated memory.
 *
 * @param data Pointer to the shared data structure
 */
void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		pthread_mutex_destroy(&data->philosophers[i].mutex);
		i++;
	}
	free(data->forks);
	free(data->philosophers);
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->print_lock);
}
