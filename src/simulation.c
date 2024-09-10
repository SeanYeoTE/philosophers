/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/10 12:54:53 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main routine for each philosopher thread
 *
 * This function implements the main loop for each philosopher.
 * It waits for the simulation to start, then alternates between
 * thinking, eating, and sleeping until the simulation ends or
 * the philosopher becomes full.
 *
 * @param arg Pointer to the philosopher structure (cast to void*)
 * @return void* Always returns NULL
 */
void *philosopher_routine(void *arg) {
	t_philo *philo = (t_philo *)arg;

	set_long(&philo->data->start_mutex, &philo->data->ready_count, get_long(&philo->data->start_mutex, &philo->data->ready_count) + 1);

	while (!get_bool(&philo->data->start_mutex, &philo->data->start_flag));
	
	// Set last_meal_time to the simulation start time
	set_long(&philo->mutex, &philo->last_meal_time, philo->data->start_time);
	usleep(philo->id * 100);
	while (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break;
		else
		{
			pick_up_forks(philo);
			eat(philo);
			put_down_forks(philo);
		
			if (get_long(&philo->mutex, &philo->times_eaten) == philo->data->max_meals && philo->data->max_meals > 0)
				set_bool(&philo->mutex, &philo->full, true);
			
			sleep_philo(philo);
			think(philo);
		}
	}
	return NULL;
}

/**
 * @brief Check if a philosopher has died
 *
 * This function checks if the time since a philosopher's last meal
 * exceeds the time_to_die parameter.
 *
 * @param philo Pointer to the philosopher structure
 * @return bool true if the philosopher has died, false otherwise
 */
static bool	philo_died(t_philo *philo)
{
	long 	elapsed;
	long	time_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	
	elapsed = get_timestamp_in_ms() - philo->data->start_time;
	elapsed = elapsed - get_long(&philo->mutex, &philo->last_meal_time);
	time_to_die = philo->data->time_to_die;
	
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

/**
 * @brief Monitor routine to check for dead philosophers
 *
 * This function runs in a separate thread and continuously checks
 * if any philosopher has died. If a philosopher dies, it ends the simulation.
 *
 * @param arg Pointer to the shared data structure (cast to void*)
 * @return void* Always returns NULL
 */
void	*monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i = 0;

	while (!get_bool(&data->start_mutex, &data->start_flag));
	
	while (!get_bool(&data->start_mutex, &data->end_simulation))
    {
        i = -1;
		while (++i < data->num_philosophers)
		{
			if (philo_died(&data->philosophers[i]))
			{
				set_bool(&data->start_mutex, &data->end_simulation, true);
				print_state_change(&data->philosophers[i], "died");
				return NULL;
			}
		}
        // usleep(1000); // Check every 1ms
    }
    return NULL;
}
