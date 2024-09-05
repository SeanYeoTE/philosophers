/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/05 17:31:59 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *data, int argc, char **argv)
{
	data->num_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->num_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		data->num_times_each_philosopher_must_eat = -1;
	data->end_simulation = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\
			[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	initialize_data(&data, argc, argv);
	if (data.num_philosophers <= 0)
	{
		printf("Error: number_of_philosophers must be greater than 0\n");
		return (1);
	}
	philosophers = malloc(data.num_philosophers * sizeof(t_philo));
	if (!philosophers)
	{
		perror("Failed to allocate memory for philosophers");
		return (1);
	}
	initialize_mutexes(&data);
	create_philosopher_threads(&data, philosophers);
	join_philosopher_threads(&data);
	destroy_mutexes(&data);
	return (0);
}
