/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:27:15 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/17 22:41:13 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;
	
	philo_nbr = philo->table->num_philos;
	
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	else
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static	void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handlle(&philo->philo_mutex, INIT);

		assign_forks(philo, table->forks, i);
	}

}

void	data_init(t_table	*table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	safe_mutex_handlle(&table->table_mutex, INIT);
	table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
	table->forks = safe_malloc(sizeof(t_fork) * table->num_philos);
	while (++i < table->num_philos)
	{
		safe_mutex_handlle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	philo_init(table);
}
