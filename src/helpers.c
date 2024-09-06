/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:54:07 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/06 16:00:03 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_timestamp_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_state_change(t_philo *philo, const char *state) {
    long timestamp = get_timestamp_in_ms() - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id + 1, state);
}

void think(t_philo *philo) {
    print_state_change(philo, "is thinking");
    usleep(rand() % 1000);
}

void eat(t_philo *philo) {
    long timestamp = get_timestamp_in_ms() - philo->data->start_time;
    set_long(&philo->mutex, &philo->last_meal_time, timestamp);
    print_state_change(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
}

void sleep_philo(t_philo *philo) {
    print_state_change(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

void pick_up_forks(t_philo *philo)
{
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % philo->data->num_philosophers;

    if (left_fork < right_fork) {
        pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
        print_state_change(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
        print_state_change(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(&philo->data->forks[right_fork].mutex);
        print_state_change(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[left_fork].mutex);
        print_state_change(philo, "has taken a fork");
    }
}

void put_down_forks(t_philo *philo) {
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % philo->data->num_philosophers;

    pthread_mutex_unlock(&philo->data->forks[right_fork].mutex);
    pthread_mutex_unlock(&philo->data->forks[left_fork].mutex);
}