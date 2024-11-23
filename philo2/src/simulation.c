/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/24 01:49:29 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* @brief Main routine for single philosopher thread
* 
* This function is used to simulate a single philosopher thread.
* It waits for the simulation to start, then waits for the simulation
* to end.
*
* @param arg Pointer to the philosopher structure (cast to void*)
* @return void* Always returns NULL
*/
void	*single_philo(void *arg)
void	*single_philo(void *arg)
{
	t_philo	*philo;
	long	timestamp;

	philo = (t_philo *)arg;
	timestamp = get_timestamp_in_ms() - philo->data->start_time;
	spinlock(&philo->data->start_mutex, &philo->data->start_flag);
	set_long(&philo->mutex, &philo->last_meal_time, philo->data->start_time);
	print_state_change(philo, "has taken a fork", timestamp);
	usleep(1000);
	while (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
		usleep(50000);
	}
	return (NULL);
}


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
void	*normal_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	spinlock(&philo->data->start_mutex, &philo->data->start_flag);
	set_long(&philo->mutex, &philo->last_meal_time, philo->data->start_time);
	unequal_sleep(philo);
	while (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
			break ;
		else if (hungriest_philosopher(philo->data, philo->id))
		{
			pick_up_forks(philo);
			sleep_philo(philo, get_timestamp_in_ms() - philo->data->start_time);
			if (get_long(&philo->mutex, &philo->times_eaten)
				== philo->data->max_meals && philo->data->max_meals > 0)
				set_bool(&philo->mutex, &philo->full, true);
			think(philo);
		}
	}
	return (NULL);
	return (NULL);
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
	long	elapsed;
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	elapsed = get_timestamp_in_ms() - philo->data->start_time;
	if (philo->data->num_philos != 1)
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
	t_data	*data;
	int		i;
	long	timestamp;

	data = (t_data *)arg;
	spinlock(&data->start_mutex, &data->start_flag);
	while (!get_bool(&data->start_mutex, &data->end_simulation))
	{
		i = -1;
		while (++i < data->num_philos && !get_bool(&data->start_mutex,
				&data->end_simulation))
		{
			if (philo_died(&data->philos[i]))
			{
				timestamp = get_timestamp_in_ms() - data->start_time;
				set_bool(&data->philos[i].mutex, &data->philos[i].dead, true);
				set_bool(&data->start_mutex, &data->end_simulation, true);
				print_state_change(&data->philos[i], "died", timestamp);
				return (NULL);
			}
		}
	}
	return (NULL);
}
