/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 16:07:37 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 20:59:19 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_philo.h"
#include "philo.h"

static int	ate_enough(t_philo *philo, int i, int full)
{
	if (is_full(&philo[i]) && philo[i].status->flag != FULL)
	{
		full++;
		philo[i].status->flag = FULL;
	}
	if (all_stuffed(&philo[i], full))
	{
		full = -1;
		lock_stop(philo);
		philo->data->stop = 1;
		unlock_stop(philo);
	}
	return (full);
}

int	single(t_philo *philo)
{
	lock_right(philo);
	log_state(philo, FORKS);
	unlock_right(philo);
	_sleep(philo, philo->data->t_die);
	return (1);
}

void	*cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (game_over(philo))
		return (NULL);
	lock_time(philo);
	philo->data->time_stamp = get_time_ms();
	if (philo->data->total == 1)
		philo->last_meal = get_time_ms();
	unlock_time(philo);
	if (philo->id % 2)
	{
		log_state(philo, SLEEP);
		_sleep(philo, philo->data->t_sleep);
	}
	while (1)
	{
		if (game_over(philo))
			return (NULL);
		if (philo->data->total == 1 && single(philo))
			continue ;
		if ((!forks(philo) || !eat(philo) || !crash(philo) || game_over(philo)))
			return (NULL);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	int			i;
	static int	full;

	full = 0;
	philo = arg;
	while (1)
	{
		if (game_over(philo))
			return (NULL);
		i = -1;
		while (++i < philo->data->total)
		{
			if (game_over(&philo[i]))
				return (NULL);
			if (is_dead(&philo[i]) && philo->status->flag != FULL)
				return (log_die(philo), NULL);
			full = ate_enough(philo, i, full);
			if (full < 0 || game_over(&philo[i]))
				return (NULL);
		}
	}
	return (NULL);
}
