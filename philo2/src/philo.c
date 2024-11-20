/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/20 14:44:04 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checks(t_data *data, char **argv)
{
	if (ft_atoi_safe(argv[1], &data->num_philos) == 0)
		return (0);
	if (ft_atoi_safe(argv[2], &data->time_to_die) == 0)
		return (0);
	if (ft_atoi_safe(argv[3], &data->time_to_eat) == 0)
		return (0);
	if (ft_atoi_safe(argv[4], &data->time_to_sleep) == 0)
		return (0);
	return (1);
}

/**
 * @brief Initialize the shared data structure
 *
 * This function parses command line arguments and
 * initializes the shared data structure.
 *
 * @param data Pointer to the shared data structure
 * @param argc Argument count
 * @param argv Array of argument strings
 * @return int 1 if initialization was successful, 0 otherwise
 */
int	initialize_data(t_data *data)
{
	data->philos = malloc(data->num_philos * sizeof(t_philo));
	if (!data->philos)
		return (0);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	set_bool(&data->start_mutex, &data->start_flag, false);
	set_bool(&data->start_mutex, &data->end_simulation, false);
	return (1);
}

int	validate_data(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (arg_checks(data, argv) == 0)
		return (0);
	if (argc == 6 && !ft_atoi_safe(argv[5], &data->max_meals))
		return (0);
	if (argc == 5)
		data->max_meals = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (data->max_meals != -1 && data->max_meals <= 0))
		return (0);
	if (initialize_data(data) == 0)
		return (0);
	return (1);
}

/**
 * @brief Main function for the dining philosophers problem
 *
 * This function initializes the simulation, creates philosopher threads,
 * starts the monitor thread, and cleans up resources at the end.
 *
 * @param argc Argument count
 * @param argv Array of argument strings
 * @return int 0 if successful, 1 if an error occurred
 */
int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (!validate_data(&data, argc, argv))
	{
		printf("Error: Input values must be non negative, within INT range\n");
		return (0);
	}
	initialize_forks(&data);
	pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	create_philosopher_threads(&data);
	join_philosopher_threads(&data);
	set_bool(&data.start_mutex, &data.end_simulation, true);
	pthread_join(monitor_thread, NULL);
	destroy_mutexes(&data);
	return (0);
}
