/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:44:01 by seayeo            #+#    #+#             */
/*   Updated: 2024/12/06 17:26:07 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	long	i;

	i = 0;
	table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		return (errormsg("Error: Malloc failed\n"), 1);
	while (i < table->num_philos)
	{
		table->forks[i].id = i;
		table->forks[i].last_used = get_time(1);
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i++;
	}
	return (0);
}

static void	init_data(t_philo *philo, int i)
{
	philo->id = i;
	philo->meals = 0;
	philo->last_meal = get_time(1);
	philo->full = false;
	philo->dead = false;
}

int	init_threads(t_table *table)
{
	long	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (errormsg("Error: Malloc failed\n"), 1);
	while (++i < table->num_philos)
	{
		pthread_mutex_init(&table->philos[i].mutex, NULL);
		init_data(&table->philos[i], i);
		table->philos[i].table = table;
		if (table->num_philos == 1)
		{
			if (!tredcreate(&table->philos[i].thread, solo, &table->philos[i]))
				return (errormsg("Error: Thread creation failed\n"), 1);
		}
		else
		{
			if (!tredcreate(&table->philos[i].thread, life, &table->philos[i]))
				return (errormsg("Error: Thread creation failed\n"), 1);
		}
	}
	assign_forks(table);
	set_long(&table->table_data, &table->start_time, get_time(1));
	return (0);
}

// left fork is id -1 and right fork is id, except for the first philosopher
int	assign_forks(t_table *table)
{
	long	i;

	i = 0;
	if (table->num_philos == 1)
		return (0);
	while (i < table->num_philos)
	{
		if (i == 0)
			table->philos[i].left_fork = &table->forks[table->num_philos - 1];
		else
			table->philos[i].left_fork = &table->forks[i - 1];
		table->philos[i].right_fork = &table->forks[i];
		i++;
	}
	return (0);
}

// set to die, eat, sleep to microseconds
int	init_others(t_table *table)
{
	pthread_mutex_init(&table->table_data, NULL);
	pthread_mutex_init(&table->print, NULL);
	table->time_to_die = table->time_to_die * 1000;
	table->time_to_eat = table->time_to_eat * 1000;
	table->time_to_sleep = table->time_to_sleep * 1000;
	table->interval = get_min_interval(table->time_to_die,
			table->time_to_eat, table->time_to_sleep);
	table->start_flag = false;
	table->end_sim = false;
	return (0);
}
