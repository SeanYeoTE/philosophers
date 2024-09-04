/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/04 16:30:10 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mealtime(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	
	while (!get_bool(philo->data->data_mutex, &philo->data->end_simulation))
	{
		// needs to eat
	
		// eating
		safe_mutex_handle(&philo->philo_mutex, LOCK);
		
		// sleeping

		// thinking
	}
}
		
		
void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_ready))
		;
}

static void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;

	while (!get_bool(data->data_mutex, &data->end_simulation))
	{
		i = -1;
		while (++i < data->num_philo)
		{
			if (get_long(data->data_mutex, &data->philos[i].last_eat) + data->time_die < gettime())
			{
				print_status(&data->philos[i], "died");
				set_bool(data->data_mutex, &data->end_simulation, true);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int		i;

	i = -1;
	if (data->max_eat == 0)
		return ;
	safe_thread_handle(&data->monitor_thread, monitor, data, CREATE);

	while (++i < data->num_philo)
		safe_thread_handle(&data->philos[i].thread, mealtime, &data->philos[i], CREATE);
	i = -1;
	while (++i < data->num_philo)
		safe_thread_handle(&data->philos[i].thread, NULL, NULL, JOIN);
	set_bool(data->data_mutex, &data->end_simulation, true);
	safe_thread_handle(&data->monitor_thread, NULL, NULL, JOIN);
}
