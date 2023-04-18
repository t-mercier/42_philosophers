/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 16:06:08 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 18:17:51 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	crash(t_philo *philo)
{
	if (game_over(philo))
		return (0);
	log_state(philo, SLEEP);
	_sleep(philo, philo->data->t_sleep);
	log_state(philo, THINK);
	return (1);
}

int	eat(t_philo *philo)
{
	if (game_over(philo))
		return (0);
	lock_time(philo);
	philo->last_meal = get_time_ms();
	unlock_time(philo);
	if (philo->data->must_eat > 0)
	{
		lock_count(philo);
		philo->eat_count++;
		unlock_count(philo);
	}
	log_state(philo, EAT);
	_sleep(philo, philo->data->t_eat);
	unlock_right(philo);
	unlock_left(philo);
	if (game_over(philo))
		return (0);
	return (1);
}

int	forks(t_philo *philo)
{
	if (game_over(philo))
		return (0);
	lock_right(philo);
	log_state(philo, FORKS);
	lock_left(philo);
	log_state(philo, FORKS);
	return (1);
}
