/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:53:14 by seayeo            #+#    #+#             */
/*   Updated: 2024/12/05 17:54:04 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	hungriest_philo(t_philo *philo)
{
	long	times[3];

	times[0] = (get_long(&philo->mutex, &philo->last_meal)) - philo->table->start_time;
	times[1] = (get_long(&philo->mutex, &philo->left_fork->last_used)) - philo->table->start_time;
	times[2] = (get_long(&philo->mutex, &philo->right_fork->last_used)) - philo->table->start_time;
	if (times[0] < 0 && times[1] < 0 && times[2] < 0)
		return (true);
	if (times[1] != times[0] && times[2] != times[0])
		return (true);
	return (false);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	spinlock(&philo->table->start_flag, &philo->table->table_data);
	set_long(&philo->mutex, &philo->last_meal, philo->table->start_time);
	desync_start(philo->id);
	while (!get_bool(&philo->table->table_data, &philo->table->end_sim))
	{
		if (get_bool(&philo->mutex, &philo->full))
			break ;
		else if (hungriest_philo(philo))
		{
			pick_fork(philo, get_time(1));
			if (get_bool(&philo->mutex, &philo->full))
				break ;
		}
	}
	// printf("%ld philo is done\n", philo->id + 1);
	return (NULL);
}

void	*solo(void *arg)
{
	t_philo		*philo;
	long		time;

	philo = (t_philo *)arg;
	spinlock(&philo->table->start_flag, &philo->table->table_data);
	set_long(&philo->mutex, &philo->last_meal, philo->table->start_time);
	usleep(1000);
	time = get_time(1) - philo->table->start_time;
	print_state_change(philo, "has taken a fork", time);
	while (!get_bool(&philo->table->table_data, &philo->table->end_sim))
	{
		usleep(50000);
		printf("philo %ld is thinking\n", philo->id + 1);
	}
	return (NULL);
}

int	is_philo_dead(t_philo *philo)
{
	long	time;
	long	last_meal;

	time = get_time(1) - philo->table->start_time;
	last_meal = get_long(&philo->mutex, &philo->last_meal);
	last_meal = last_meal - philo->table->start_time;
	if (last_meal >= 0
		&& time - last_meal > philo->table->time_to_die)
		return (1);
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;
	long	i;
	long	time;

	table = (t_table *)arg;
	spinlock(&table->start_flag, &table->table_data);
	set_long(&table->table_data, &table->start_time, get_time(1));
	while (!get_bool(&table->table_data, &table->end_sim))
	{
		i = 0;
		while (++i < table->num_philos &&
			!get_bool(&table->table_data, &table->end_sim))
		{
			time = get_time(1) - table->start_time;
			if (is_philo_dead(&table->philos[i]))
			{
				set_bool(&table->philos[i].mutex, &table->philos[i].dead, true);
				set_bool(&table->table_data, &table->end_sim, true);
				print_state_change(&table->philos[i], "died", time);
				return (NULL);
			}
		}
		// usleep(table->interval);
	}
	return (NULL);
}
