/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/08 22:35:12 by seayeo           ###   ########.fr       */
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
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(&philo->data->start_mutex, &philo->data->ready_count,
		get_long(&philo->data->start_mutex, &philo->data->ready_count) + 1);
	while (!get_bool(&philo->data->start_mutex, &philo->data->start_flag))
		;
	set_long(&philo->mutex, &philo->last_meal_time, philo->data->start_time);
	print_state_change(philo, "has taken a fork");
	usleep(1000);
	while (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
		usleep(50000);
	return (NULL);
}

void	unequal_sleep(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(200);
	else
		usleep(0);
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
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(&philo->data->start_mutex, &philo->data->ready_count,
		get_long(&philo->data->start_mutex, &philo->data->ready_count) + 1);
	while (!get_bool(&philo->data->start_mutex, &philo->data->start_flag))
		;
	set_long(&philo->mutex, &philo->last_meal_time, philo->data->start_time);
	unequal_sleep(philo);
	while (!get_bool(&philo->data->start_mutex, &philo->data->end_simulation))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		else if (hungriest_philosopher(philo->data, philo->id))
		{
			pick_up_forks(philo);
			sleep_philo(philo);
			if (get_long(&philo->mutex, &philo->times_eaten)
				== philo->data->max_meals && philo->data->max_meals > 0)
				set_bool(&philo->mutex, &philo->full, true);
			think(philo);
		}
	}
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
	long	time_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	elapsed = get_timestamp_in_ms() - philo->data->start_time;
	if (philo->data->num_philosophers != 1)
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
	int i;

	while (!get_bool(&data->start_mutex, &data->start_flag));
	
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (!get_bool(&data->start_mutex, &data->start_flag))
		;
	while (!get_bool(&data->start_mutex, &data->end_simulation))
	{
		// printf("monitor\n");
		i = -1;
		while (++i < data->num_philosophers && !get_bool(&data->start_mutex, &data->end_simulation))
	{
		i = -1;
		while (++i < data->num_philosophers && !get_bool(&data->start_mutex,
				&data->end_simulation))
		{
			if (philo_died(&data->philosophers[i]))
			{
				set_bool(&data->philosophers[i].mutex,
					&data->philosophers[i].dead, true);
				set_bool(&data->start_mutex, &data->end_simulation, true);
				print_state_change(&data->philosophers[i], "died");
				return (NULL);
			}
		}
		// usleep(500); // Check every 1ms
	}
	return NULL;
	}
	return (NULL);
}
