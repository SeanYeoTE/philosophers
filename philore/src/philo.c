/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:41:49 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 20:10:08 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (errormsg("Error: Invalid number of arguments"), 1);
	if (ft_atol_assign(argv[1], table->num_philos))
		return (errormsg("Error: Invalid number of philosophers"), 1);
	if (ft_atol_assign(argv[2], table->time_to_die))
		return (errormsg("Error: Invalid time to die"), 1);
	if (ft_atol_assign(argv[3], table->time_to_eat))
		return (errormsg("Error: Invalid time to eat"), 1);
	if (ft_atol_assign(argv[4], table->time_to_sleep))
		return (errormsg("Error: Invalid time to sleep"), 1);
	if (argc == 6)
	{
		if (ft_atol_assign(argv[5], table->num_meals))
			return (errormsg("Error: Invalid number of meals"), 1);
	}
	else
		table->num_meals = -1;
	if (table->num_philos < 2 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60
		|| (argc == 6 && table->num_meals < 1))
		return (errormsg("Error: Invalid arguments\n"), 1);
	return (0);
}

int	start_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_philos == 1)
	{
		if (thread_creation(&table->philos[0].thread, &solo, &table->philos[0]))
			return (errormsg("Error: Thread creation failed\n"), 1);
	}
	else
	{
		while (i < table->num_philos)
		{
			if (thread_creation(&table->philos[i].thread, &philo_life, &table->philos[i]))
				return (errormsg("Error: Thread creation failed\n"), 1);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table table;

	if (check_args(argc, argv, &table))
		return (1);
	if (init_others(&table))
		return (1);
	if (init_forks(&table))
		return (1);
	if (init_threads(&table))
		return (1);
	if (start_threads(&table))
		return (1);
	
	

}
