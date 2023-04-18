/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 16:01:17 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 18:30:01 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_philo.h"
#include "philo.h"

int	game_over(t_philo *philo)
{
	lock_stop(philo);
	if (philo->data->stop)
	{
		unlock_stop(philo);
		return (1);
	}
	unlock_stop(philo);
	return (0);
}

int	is_full(t_philo *philo)
{
	int	full;

	if (game_over(philo))
		return (-1);
	lock_count(philo);
	full = 0;
	if (philo->data->must_eat > 0
		&& philo->eat_count >= philo->data->must_eat)
		full = 1;
	unlock_count(philo);
	return (full);
}

int	is_dead(t_philo *philo)
{
	uint64_t	dt;

	if (game_over(philo))
		return (1);
	lock_time(philo);
	dt = get_time_ms() - philo->last_meal;
	unlock_time(philo);
	if (dt >= philo->data->t_die)
	{
		lock_stop(philo);
		philo->data->stop = 1;
		unlock_stop(philo);
		return (1);
	}
	return (0);
}

int	all_stuffed(t_philo *philo, int full)
{
	if (game_over(philo))
		return (1);
	if (full >= philo->data->total)
	{
		lock_stop(philo);
		philo->data->stop = 1;
		unlock_stop(philo);
		return (1);
	}
	return (0);
}
