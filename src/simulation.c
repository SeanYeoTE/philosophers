/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:18:26 by seayeo            #+#    #+#             */
/*   Updated: 2024/08/02 18:14:37 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_hungriest(t_philo *philo)
{
	int	i;
	long	last_meal;
	long	prev_last_meal;
	long	next_last_meal;

	i = philo->id;
	last_meal = get_long(philo->philo_mutex, &philo->last_eat);
	prev_last_meal = get_long(philo->data->philos[i - 1].philo_mutex, &philo->data->philos[i - 1].last_eat);
	next_last_meal = get_long(philo->data->philos[i + 1].philo_mutex, &philo->data->philos[i + 1].last_eat);
	if (last_meal > prev_last_meal && last_meal > next_last_meal)
		return (true);
	return (false);
}

static void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	
	print_status(philo, "is thinking");
	if (check_hungriest(philo))
		return ;
	if (philo->data->num_philo % 2 == 0)
		return ;
	t_eat = philo->data->time_eat;
	t_sleep = philo->data->time_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	usleep(t_think * 1000);
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
	set_long_nl(&forks[philo->left_fork].time_last_used, eating_time);
	set_long_nl(&forks[philo->right_fork].time_last_used, eating_time);
	print_status(philo, "is eating");
	philo->eat_count++;
	usleep(philo->data->time_eat * 1000);
	
	safe_mutex_handle(&forks[philo->left_fork].fork_mutex, UNLOCK);
	safe_mutex_handle(&forks[philo->right_fork].fork_mutex, UNLOCK);
}

void	*mealtime(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	puts("mealtime");
	print_status(philo, "idling");
	while(!simulation_finished(philo->data))
	{
		if (get_bool(philo->philo_mutex, &philo->full))
			break ;
		else
		{
			eat(philo);

			sleeping(philo);
			
			if (philo->data->max_eat > 0 && philo->eat_count == philo->data->max_eat)
				set_bool(philo->philo_mutex, &philo->full, true);
			
			thinking(philo);
		}
	}
	return (NULL);
}

void	*monitor(void *data)
{
	int	i;
	t_data *d;

	d = (t_data *)data;
	
	while (get_bool(d->data_mutex, &d->end_simulation) == false)
	{
		i = -1;
		while (++i < d->num_philo)
		{
			if (gettime() - d->philos[i].last_eat > d->time_die)
			{
				print_status(&d->philos[i], "died");
				set_bool(d->data_mutex, &d->end_simulation, true);
				break ;
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
	data->start_time = gettime();
	i = -1;
	while (++i < data->num_philo)
		safe_thread_handle(&data->philos[i].thread, NULL, NULL, JOIN);
	set_bool(data->data_mutex, &data->end_simulation, true);
	safe_thread_handle(&data->monitor_thread, NULL, NULL, JOIN);
}
