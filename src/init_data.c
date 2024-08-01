/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/08/01 13:32:46 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_philos(t_data *data)
{
    int     i;
    t_philo *philo;
    
    i = -1;
    while (++i < data->num_philo)
    {
        philo = &data->philos[i];
        philo->id = i;
        philo->left_fork = i;
        philo->right_fork = (i + 1) % data->num_philo;
        philo->eat_count = 0;
        philo->last_eat = gettime();
        philo->full = false;
        philo->data = data;
        safe_mutex_handle(&philo->philo_mutex, INIT);
    }
}

void    init_data(t_data *data)
{
    int i;

    i = -1;
    data->end_simulation = false;
    data->threads_running = 0;
    safe_mutex_handle(&data->data_mutex, INIT);

    data->philos = safe_malloc(sizeof(t_philo) * data->num_philo);
    data->forks = safe_malloc(sizeof(t_fork) * data->num_philo);
    
    while (++i < data->num_philo)
    {
        safe_mutex_handle(&data->forks[i].fork_mutex, INIT);
        data->forks[i].id = i;
        data->forks[i].time_last_used = gettime();
    }
    init_philos(data);
}