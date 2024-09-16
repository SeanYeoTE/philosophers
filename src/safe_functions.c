/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:46:05 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/16 18:03:07 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Safely get a boolean value
 *
 * This function uses a mutex to safely retrieve a boolean value.
 *
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the boolean value
 * @return bool The retrieved boolean value
 */
bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * @brief Safely set a boolean value
 *
 * This function uses a mutex to safely set a boolean value.
 *
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the boolean value to be set
 * @param new_value The new boolean value
 */
void	set_bool(pthread_mutex_t *mutex, bool *value, bool new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

/**
 * @brief Safely get a long value
 *
 * This function uses a mutex to safely retrieve a long value.
 *
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the long value
 * @return long The retrieved long value
 */
long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * @brief Safely set a long value
 *
 * This function uses a mutex to safely set a long value.
 *
 * @param mutex Pointer to the mutex protecting the value
 * @param value Pointer to the long value to be set
 * @param new_value The new long value
 */
void	set_long(pthread_mutex_t *mutex, long *value, long new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}
