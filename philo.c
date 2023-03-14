/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 09:47:45 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/14 18:30:05 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ARGS
 * number_of_philosophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
 */

#include "philo.h"
#include <stddef.h>
#include <time.h>

void *_dies(void *arg) {
	t_philo *philo;
	int i;

	philo = (t_philo *) arg;
	i = 0;
	while (i < philo->args.total) {
		if (is_dead(&philo[i])) {
			log_msg(philo, DIE);
			pthread_mutex_lock(&philo->_end);
			philo->is_dead = true;
			pthread_mutex_unlock(&philo->_end);
		}
		i++;
	}
	return (NULL);
}

void release(t_philo *philo) {
	pthread_mutex_unlock(&philo->_fork[philo->right]);
	pthread_mutex_unlock(&philo->_fork[philo->left]);
	log_msg(philo, SLEEP);
	_usleep(philo->args.t_sleep);
	log_msg(philo, THINK);
}

void eats(t_philo *philo) {
	get_time(&philo->last_eat);
	philo->is_eating = true;
	log_msg(philo, EAT);
	philo->eat_count++;
	_usleep(philo->args.t_eat);
}

void take_forks(t_philo *philo) {
	pthread_mutex_lock(&philo->_fork[philo->right]);
	log_msg(philo, FORK);
	pthread_mutex_lock(&philo->_fork[philo->left]);
	log_msg(philo, FORK);
}

void *_routine(void *arg) {
	t_philo *philo = (t_philo *) arg;
	while (1) {
		if (is_dead(philo)) {
			log_msg(philo, DIE);
			pthread_mutex_lock(&philo->_end);
			philo->is_dead = true;
			pthread_mutex_unlock(&philo->_end);
			return NULL;
		}
		take_forks(philo);
		eats(philo);
		release(philo);
	}
	return NULL;
}

void start_simulation(t_philo *philo, t_args *args) {

	pthread_t death_t;
	int i = 0;
	while (i < args->total) {
		pthread_create(&philo[i].id_t, NULL, _routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < args->total) {
		pthread_join(philo[i].id_t, NULL);
		i++;
	}
}

t_args init_data(int ac, char **av) {
	t_args args;
	args.total = (int) ft_strtol(av[1]);
	args.t_die = (int) ft_strtol(av[2]);
	args.t_eat = (int) ft_strtol(av[3]);
	args.t_sleep = (int) ft_strtol(av[4]);
	args.must_eat = 0;
	if (ac == 6)
		args.must_eat = (int) ft_strtol(av[5]);
	if (args.total < 2 || args.total > 200)
		printf("Error: invalid number of philosophers.\n");
	return args;
}

int main(int ac, char **av) {
	t_philo *philo;
	t_args args;

	args = init_data(ac, av);
	philo = malloc(sizeof(t_philo) * args.total);
	init_status(philo);
	// fprintf(stderr, "%d")
	init_philo(philo, args);
	pthread_mutex_init(&philo->_end, NULL);
	start_simulation(philo, &args);
	int i = 0;
	while (i < philo->args.total)
		pthread_mutex_destroy(&philo->_fork[i++]);
	pthread_mutex_destroy(&philo->_end);
	return 0;
}
