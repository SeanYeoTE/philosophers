/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/06 16:04:04 by seayeo           ###   ########.fr       */
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
	 while (!get_bool(&philo->data->start_mutex, &philo->data->start_flag));
	
	philo->data->start_time = get_timestamp_in_ms();
	usleep(philo->id * 100);
	
	pthread_mutex_lock(&philo->mutex);
    philo->last_meal_time = get_timestamp_in_ms();
    pthread_mutex_unlock(&philo->mutex);
	
	while (!philo->data->end_simulation) {
		
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if (philo->times_eaten == philo->data->max_meals && philo->data->max_meals > 0)
			set_bool(&philo->mutex, &philo->full, true);
		sleep_philo(philo);
		think(philo);
	}
	return NULL;
}

static bool	philo_died(t_philo *philo)
{
	long 	elapsed;
	long	time_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	
	elapsed = get_timestamp_in_ms() - get_long(&philo->mutex, &philo->last_meal_time);
	time_to_die = philo->data->time_to_die;
	
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i = 0;

	while (!get_bool(&data->start_mutex, &data->end_simulation))
    {
        i = -1;
		while (++i < data->num_philosophers)
		{
			if (philo_died(&data->philosophers[i]))
			{
				print_state_change(&data->philosophers[i], "died");
				set_bool(&data->start_mutex, &data->end_simulation, true);
				// pthread_mutex_lock(&data->start_mutex);
				// data->end_simulation = true;
				// pthread_mutex_unlock(&data->start_mutex);
				return NULL;
			}
		}
        usleep(1000); // Check every 1ms
    }
    return NULL;
}
