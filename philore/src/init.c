/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:44:01 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 21:44:29 by seayeo           ###   ########.fr       */
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
		table->forks[i].last_used = 0;
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i++;
	}
	return (0);
}

int	init_threads(t_table *table)
{
	long	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (errormsg("Error: Malloc failed\n"), 1);
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->philos[i].mutex, NULL);
		table->philos[i].id = i;
		table->philos[i].meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		i++;
	}
	assign_forks(table);
	pthread_mutex_init(&table->print, NULL);
	table->start_time = get_time();
	return (0);
}

// left fork is id -1 and right fork is id, except for the first philosopher
int	assign_forks(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (i == 0)
			table->philos[i].left_fork
				= &table->forks[table->num_philos - 1].mutex;
		else
			table->philos[i].left_fork = &table->forks[i - 1].mutex;
		table->philos[i].right_fork = &table->forks[i].mutex;
		i++;
	}
	return (0);
}
// set to die, eat, sleep to microseconds
int init_others(t_table *table)
{
	pthread_mutex_init(&table->table_data, NULL);
	table->start_flag = false;
	table->time_to_die = table->time_to_die * 1000;
	table->time_to_eat = table->time_to_eat * 1000;
	table->time_to_sleep = table->time_to_sleep * 1000;
	return (0);
}