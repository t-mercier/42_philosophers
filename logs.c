/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logs.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 16:03:53 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 20:52:30 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_philo.h"
#include "philo.h"

void	log_die(t_philo *philo)
{
	uint64_t	time;

	lock_time(philo);
	time = current_time_ms(philo);
	unlock_time(philo);
	printf("%s%llu\t%d %s\n\x1b[0m",
		philo->status[DIE].c,
		time,
		philo->id + 1,
		philo->status[DIE].msg);
}

void	log_state(t_philo *philo, int state)
{
	uint64_t	time;

	if (game_over(philo))
		return ;
	lock_time(philo);
	time = current_time_ms(philo);
	unlock_time(philo);
	printf("%llu\t%d %s\n",
		time,
		philo->id + 1,
		philo->status[state].msg);
}

void	status(t_philo *philo)
{
	philo->status[0] = (t_status){FORKS, "has taken a fork", ""};
	philo->status[1] = (t_status){EAT, "is eating", GREEN};
	philo->status[2] = (t_status){SLEEP, "is sleeping", ""};
	philo->status[3] = (t_status){THINK, "is thinking", ""};
	philo->status[4] = (t_status){DIE, "died", PURPLE};
	philo->status[5] = (t_status){FULL, NULL, NULL};
	philo->status[6] = (t_status){RELEASE, "released 1 fork", BLUE};
}
