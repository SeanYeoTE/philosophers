/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/06 15:56:09 by seayeo           ###   ########.fr       */
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
		data->max_meals = atoi(argv[5]);
	else
		data->max_meals = -1;
    data->end_simulation = false;
    data->philosophers = NULL;
    data->forks = NULL;
    data->ready_count = 0;
    data->start_flag = false;

    pthread_mutex_init(&data->start_mutex, NULL);
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
	data.philosophers = philosophers;
	initialize_mutexes(&data);

	pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	
	create_philosopher_threads(&data, philosophers);
	join_philosopher_threads(&data);
	
	pthread_join(monitor_thread, NULL);
	
	destroy_mutexes(&data);
	return (0);
}
