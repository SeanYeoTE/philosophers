/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/05 18:35:02 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_mutexes(t_data *data) {
    data->forks = malloc(data->num_philosophers * sizeof(pthread_mutex_t));
    if (!data->forks) {
        perror("Failed to allocate memory for forks");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < data->num_philosophers) {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->start_mutex, NULL);
}

void create_philosopher_threads(t_data *data, t_philo *philosophers) {
    data->philosophers = malloc(data->num_philosophers * sizeof(pthread_t));
    if (!data->philosophers) {
        perror("Failed to allocate memory for philosophers");
        exit(EXIT_FAILURE);
    }

    data->ready_count = 0;
    data->start_flag = 0;

    int i = 0;
    while (i < data->num_philosophers) {
        philosophers[i].id = i;
        philosophers[i].data = data;
        philosophers[i].times_eaten = 0;
        philosophers[i].last_meal_time = 0;
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
        i++;
    }

    // Wait until all threads are ready
    while (data->ready_count < data->num_philosophers);

    // Set the start flag to release all threads
    data->start_flag = 1;
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
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    free(data->philosophers);

    pthread_mutex_destroy(&data->start_mutex);
}