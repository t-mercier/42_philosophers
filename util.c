/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 13:33:12 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/14 18:27:44 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void init_status(t_philo *philo) {
	philo->status[0] = (t_status){EAT, "is eating"};
	philo->status[1] = (t_status){FORK, "has taken a fork"};
	philo->status[2] = (t_status){SLEEP, "is sleeping"};
	philo->status[3] = (t_status){THINK, "is thinking"};
	philo->status[4] = (t_status){DIE, "died"};
}

uint64_t get_time(uint64_t *prev) {
	struct timeval now;

	gettimeofday(&now, 0);
	uint64_t curr = now.tv_usec / 1000 + now.tv_sec * (uint64_t) 1000;
	if (*prev == 0) {
		*prev = curr;
		}
		uint64_t new = curr - *prev;
		*prev = curr;
		return (new);
}

void _usleep(uint64_t tms) {
	usleep(tms * 1000);
}

void log_msg(t_philo *philo, enum e_state state) {
	static int _stop = 0;

	uint64_t t = get_time(&philo->currtime);
	philo->runtime += t;
	if (!_stop) {
		fprintf(stderr, "%llu\t%d %s\n", philo->runtime, philo->id, philo->status[state].msg);
		if (philo->state == DEAD || philo->state == END)
		
			_stop = 1;
	}
}

bool is_dead(t_philo *philo) {

	if (!(philo->is_eating) && (get_time(&philo->last_eat) > (philo->args.t_die)))
		return true;
	return false;
}

void init_philo(t_philo *philo, t_args args) {
	pthread_mutex_t *fork = malloc(sizeof(pthread_mutex_t) * args.total);

	int i = 0;
	while (i < args.total) {
		memset(&philo[i], 0, sizeof(t_philo));
		init_status(&philo[i]);
		philo[i].args = args;
		philo[i].id = i + 1;
		philo[i].is_eating = false;
		philo[i].is_dead = false;
		philo[i].eat_count = 0;
		philo[i].last_eat = 0;
		philo[i].state = 0;
		philo[i].left = i + 1;
		philo[i].right = (i + 2) % (philo->args.total);
		philo[i]._fork = fork;
		i++;
	}
	i = 0;
	while (i < args.total) {
		pthread_mutex_init(&philo->_fork[i], NULL);
		i++;
	}
}