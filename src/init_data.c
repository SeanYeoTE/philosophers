/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/06 15:56:26 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    initialize_mutexes(t_data *data)
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

void create_philosopher_threads(t_data *data, t_philo *philosophers)
{
    data->philosophers = malloc(data->num_philosophers * sizeof(t_philo));
    if (!data->philosophers) {
        perror("Failed to allocate memory for philosophers");
        exit(EXIT_FAILURE);
    }

    data->ready_count = 0;
    data->start_flag = 0;

    int i = 0;
    while (i < data->num_philosophers) {
        philosophers[i].id = i;
        philosophers[i].last_meal_time = get_timestamp_in_ms();
        philosophers[i].data = data;
        philosophers[i].times_eaten = 0;
        philosophers[i].full = false;
        pthread_mutex_init(&philosophers[i].mutex, NULL);
        if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]) != 0) {
            perror("Failed to create philosopher thread");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Wait until all threads are ready
    while (data->ready_count < data->num_philosophers);

    // Set the start flag to release all threads
    set_bool(&data->start_mutex, &data->start_flag, true);
}

void join_philosopher_threads(t_data *data) {
    int i = 0;
    while (i < data->num_philosophers) {
        pthread_join(data->philosophers[i].thread, NULL);
        i++;
    }
}

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
