/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    simulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/29 15:21:50 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(philo->data->time_think * 1000);
}

static void	eat(t_philo *philo)
{
	long	eating_time;
	t_fork	*forks;
	
	forks = philo->data->forks;
	eating_time = gettime();
	safe_mutex_handle(&forks[philo->left_fork].fork_mutex, LOCK);
	print_status(philo, "has taken a fork");
	safe_mutex_handle(&forks[philo->right_fork].fork_mutex, LOCK);
	print_status(philo, "has taken a fork");
	set_long(&philo->philo_mutex, &philo->last_eat, eating_time);
	set_long(&forks[philo->left_fork].time_last_used, eating_time);
	set_long(&forks[philo->right_fork].time_last_used, eating_time);
	print_status(philo, "is eating");
	philo->eat_count++;
	usleep(philo->data->time_eat * 1000);
	
	safe_mutex_handle(&forks[philo->left_fork].fork_mutex, UNLOCK);
	safe_mutex_handle(&forks[philo->right_fork].fork_mutex, UNLOCK);
}

void	mealtime(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;

	while(!simulation_finished(philo->data))
	{
		if (get_bool(philo->philo_mutex, &philo->full))
			break ;
		else
		{
			eat(philo);

			sleeping(philo);
			
			if (philo->data->max_eat > 0 && philo->eat_count == philo->data->max_eat)
				set_bool(philo->philo_mutex, philo->full, true);
			
			thinking(philo);
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
	data->start_time = gettime();
	i = -1;
	while (++i < data->num_philo)
		safe_thread_handle(&data->philos[i].thread, NULL, NULL, JOIN);
	set_bool(data->data_mutex, data->end_simulation, true);
	safe_thread_handle(&data->monitor_thread, NULL, NULL, JOIN);
}
