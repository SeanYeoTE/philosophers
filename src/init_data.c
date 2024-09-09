/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/09 18:17:35 by seayeo           ###   ########.fr       */
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
void    initialize_forks(t_data *data)
{
    data->forks = malloc(data->num_philosophers * sizeof(t_fork));
    if (!data->forks) {
        perror("Failed to allocate memory for forks");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < data->num_philosophers) {
        pthread_mutex_init(&data->forks[i].mutex, NULL);
        i++;
    }
}

/**
 * @brief Create threads for each philosopher
 *
 * This function initializes philosopher structures and creates threads for each philosopher.
 *
 * @param data Pointer to the shared data structure
 */
void create_philosopher_threads(t_data *data)
{
    int i = 0;
    t_philo *philo;
    
    data->philosophers = malloc(data->num_philosophers * sizeof(t_philo));
    if (!data->philosophers) {
        perror("Failed to allocate memory for philosophers");
        exit(EXIT_FAILURE);
    }

    
    while (i < data->num_philosophers) {
        philo = &data->philosophers[i];
        philo->id = i;
        philo->last_meal_time = get_timestamp_in_ms();
        philo->data = data;
        philo->times_eaten = 0;
        philo->full = false;
        pthread_mutex_init(&data->philosophers[i].mutex, NULL);
        if (pthread_create(&philo->thread, NULL, philosopher_routine, philo) != 0) {
            perror("Failed to create philosopher thread");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Set the start flag to release all threads
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
void join_philosopher_threads(t_data *data) {
    int i = 0;
    while (i < data->num_philosophers) {
        pthread_join(data->philosophers[i].thread, NULL);
        i++;
    }
}

/**
 * @brief Destroy all mutexes and free allocated memory
 *
 * This function cleans up resources by destroying mutexes and freeing allocated memory.
 *
 * @param data Pointer to the shared data structure
 */
void destroy_mutexes(t_data *data) {
    int i = 0;
    while (i < data->num_philosophers) {
        pthread_mutex_destroy(&data->forks[i].mutex);
        pthread_mutex_destroy(&data->philosophers[i].mutex);
        i++;
    }
    free(data->forks);
    free(data->philosophers);

    pthread_mutex_destroy(&data->start_mutex);
}
