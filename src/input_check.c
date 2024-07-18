/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:37 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/17 16:48:11 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int len;
	const char *number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("No Negative number");
	if (!is_digit(*str))
		error_exit("Invalid number");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Number too large");
	return (number);
}

static	long	converter(const char *str)
{
	long num;
	
	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		++str;
	}
	if (num > INT_MAX)
		error_exit("Number too large");
	return (num);
}
void	input_check(t_table *table, char **argv)
{
	table->num_philos = converter(argv[1]);
	table->time_to_die = converter(argv[2]) * 1000; // taking microseconds
	table->time_to_eat = converter(argv[3]) * 1000;
	table->time_to_sleep = converter(argv[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000 || table->time_to_sleep < 60000)
		error_exit("Time too small");
	if (argv[5])
		table->num_meals = converter(argv[5]);
	else
		table->num_meals = -1;
}