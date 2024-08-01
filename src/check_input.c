/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:17:09 by seayeo            #+#    #+#             */
/*   Updated: 2024/08/01 13:47:55 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	char	*input_rejection(char *str)
{
	int		i;
	char 	*temp;
	i = 0;
	while (*str == ' ')
		str++;
	if (*str == '-')
		write_error("Error: Invalid argument");
	else if (*str == '+')
		str++;
	temp = str;
	while (str[i] && i < 10)
	{
		if (str[i] < '0' || str[i] > '9')
			write_error("Error: Invalid argument");
		i++;
	}
	if (i > 10)
		write_error("Error: Invalid argument");
	return (temp);
}

static	long	converter(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	input_rejection(str);
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		write_error("Error: Invalid argument");
	return (num);
}

// time is stored in milliseconds
// max_eat is optional, set to -1 if not provided
void	check_input(char **argv, t_data *data)
{
	data->num_philo = converter(argv[1]);
	data->time_die = converter(argv[2]);
	data->time_eat = converter(argv[3]);
	data->time_sleep = converter(argv[4]);
	if (argv[5])
		data->max_eat = converter(argv[5]);
	else
		data->max_eat = -1;
}
