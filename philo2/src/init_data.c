/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/11 20:33:15 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		printf("Failed to allocate memory for forks");
		return ;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		data->forks[i].last_used = 0;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
}

static void	init_data(t_philo *philo, int i)
{
	philo->id = i;
	philo->last_meal_time = get_timestamp_in_ms();
	philo->times_eaten = 0;
	philo->full = false;
	philo->dead = false;
}

/**
 * @brief Create threads for each philosopher
 *
 * This function initializes philosopher structures and 
 * creates threads for each philosopher.
 *
 * @param data Pointer to the shared data structure
 */
void	create_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->num_philosophers)
	{
		philo = &data->philosophers[i];
		philo->data = data;
		init_data(philo, i);
		pthread_mutex_init(&data->philosophers[i].mutex, NULL);
		if (data->num_philosophers == 1)
		{
			if (thread_creation(&philo->thread, single_philo, philo) == 0)
				return ;
		}
		else
		{
			if (thread_creation(&philo->thread, philosopher_routine,
					philo) == 0)
				return ;
		}
		i++;
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
 * This function cleans up resources by destroying mutexes
 * and freeing allocated memory.
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
