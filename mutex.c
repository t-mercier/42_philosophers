/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 13:33:12 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 18:31:04 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_mutexes(t_fork *fork, t_data *data)
{
	int	n;

	n = 0;
	while (n < N)
	{
		if (pthread_mutex_destroy(&data->lock[n++].mutex) < 0)
			return (error(ERR_MUTEX), -1);
	}
	n = 0;
	while (n < data->total)
		if (pthread_mutex_destroy(&fork[n++].mutex) < 0)
			return (error(ERR_MUTEX), -1);
	return (0);
}

int	initialize_mutexes(t_data *data)
{
	int	n;

	n = 0;
	while (n < N)
	{
		data->lock[n].mutex_id = (enum e_mutex)n;
		if (pthread_mutex_init(&data->lock[n].mutex, NULL) < 0)
			return (error(ERR_MUTEX), -1);
		n++;
	}
	return (0);
}
