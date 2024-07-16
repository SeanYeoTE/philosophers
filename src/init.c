/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:27:15 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/16 21:42:52 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;
	
	philo_nbr = philo->table->num_philos;
	
	philo->right_fork = &forks[philo_position];
	philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	
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

		assign_forks(philo, table->forks, i);
	}

}
void	data_init(t_table	*table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
	table->forks = safe_malloc(sizeof(t_fork) * table->num_philos);
	while (++i < table->num_philos)
	{
		safe_mutex_handlle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	philo_init(table);
}