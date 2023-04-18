/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 17:59:03 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 20:59:17 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / (uint64_t)1000);
}

void	_sleep(t_philo *philo, uint64_t time)
{
	uint64_t	t;

	if (game_over(philo))
		return ;
	t = get_time_ms();
	while (get_time_ms() - t <= time)
	{
		if (game_over(philo))
			break ;
		usleep(250);
	}
}

uint64_t	current_time_ms(t_philo *philo)
{
	uint64_t	time;
	uint64_t	current_time;

	current_time = get_time_ms();
	time = current_time - philo->data->time_stamp;
	return (time);
}
