/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:41:49 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/24 01:24:10 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (errormsg("Error: Invalid number of arguments"), 1);
	if (ft_atol_assign(argv[1], &table->num_philos))
		return (errormsg("Error: Invalid number of philosophers"), 1);
	if (ft_atol_assign(argv[2], &table->time_to_die))
		return (errormsg("Error: Invalid time to die"), 1);
	if (ft_atol_assign(argv[3], &table->time_to_eat))
		return (errormsg("Error: Invalid time to eat"), 1);
	if (ft_atol_assign(argv[4], &table->time_to_sleep))
		return (errormsg("Error: Invalid time to sleep"), 1);
	if (argc == 6)
	{
		if (ft_atol_assign(argv[5], &table->num_meals))
			return (errormsg("Error: Invalid number of meals"), 1);
	}
	else
		table->num_meals = -1;
	if (table->num_philos <= 0 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60)
		return (errormsg("Error: Invalid arguments\n"), 1);
	return (0);
}

int	start_threads(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	if (table->num_philos == 1)
	{
		philo = &table->philos[0];
		if (!thread_creation(&philo->thread, solo, philo))
			return (errormsg("Error: Thread creation failed\n"), 1);
	}
	else
	{
		while (i < table->num_philos)
		{
			philo = &table->philos[i];
			if (!thread_creation(&philo->thread, philo_life, philo))
				return (errormsg("Error: Thread creation failed\n"), 1);
			i++;
		}
	}
	printf("Simulation started\n");
	set_bool(&table->table_data, &table->start_flag, true);
	return (0);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}	
}
void	destroy_everything(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->philos[i].mutex);
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&table->table_data);
	pthread_mutex_destroy(&table->print);
	free(table->philos);
	free(table->forks);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitor_thread;

	if (check_args(argc, argv, &table))
		return (1);
	if (init_others(&table))
		return (1);
	if (init_forks(&table))
		return (1);
	pthread_create(&monitor_thread, NULL, monitor, &table);
	if (init_threads(&table))
		return (1);
	if (start_threads(&table))
		return (1);
	join_threads(&table);
	set_bool(&table.table_data, &table.end_sim, true);
	pthread_join(monitor_thread, NULL);
	destroy_everything(&table);
}
