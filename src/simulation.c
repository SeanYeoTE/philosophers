/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/05 18:43:37 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg) {
	t_philo *philo = (t_philo *)arg;

	// Increment the ready count
	pthread_mutex_lock(&philo->data->start_mutex);
	philo->data->ready_count++;
	pthread_mutex_unlock(&philo->data->start_mutex);

	// Busy-wait until the start flag is set
	while (!philo->data->start_flag);

	usleep(philo->id * 100);
	
	philo->data->start_time = get_timestamp_in_ms();
	while (!philo->data->end_simulation) {
		
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		think(philo);
	}
	return NULL;
}

void	*monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i = 0;

    while (!data->end_simulation)
    {
        long current_time = get_timestamp_in_ms();
        if (current_time - data->philosophers[i].last_meal_time > data->time_to_die)
        {
            data->end_simulation = 1;
            print_state_change(&data->philosophers[i], "died");
            break;
        }
        i = (i + 1) % data->num_philosophers;
        usleep(1000); // Check every 1ms
    }
    return NULL;
}