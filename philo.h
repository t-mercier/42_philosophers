/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 09:42:53 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/14 18:28:44 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

* ARGS
	./philo 4 410 200 200
			+-------------- philo_nb
				+---------- time_die
					+------ time_eat
						+-- time_slp
 * FORMAT
	timestamp_in_ms X has taken a fork
	timestamp_in_ms X is eating
	timestamp_in_ms X is sleeping
	timestamp_in_ms X is thinking
	timestamp_in_ms X died

 Minimum time_die for EVEN philo_nb:  2 x time_eat + e

 */

#ifndef PHILO_H
#define PHILO_H

#include "../libs/inc/lib42.h"
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define LOCK pthread_mutex_lock
#define UNLOCK pthread_mutex_unlock
#define INIT pthread_mutex_init
#define EATS 0
#define FORKS 1
#define SLEEPS 2
#define THINKS 3
#define DEAD 4
#define END 5


typedef struct s_philo t_philo;
typedef struct s_args t_args;
typedef struct s_threads t_threads;
typedef struct s_mutex t_mutex;
typedef struct s_status t_status;
typedef struct s_monitor t_monitor;

enum e_state {
	EAT,
	FORK,
	SLEEP,
	THINK,
	DIE,
};

// index of the left neighbor of philosopher i,
// for whom both forks are available
static inline size_t left(size_t i, size_t total)
{
	return ((i - 1 + total) % total);
}

// number of the right neighbour of the philosopher i,
// for whom both forks are available
static inline size_t right(size_t i, size_t total)
{
	return ((i + 1) % total);
}

struct s_status {
	enum e_state state;
	const char *msg;
};

struct s_args
{
	int total;
	int t_die;
	int t_eat;
	int t_sleep;
	int must_eat;
};


struct s_philo {
	int id;
	int eat_count;
	uint64_t last_eat;
	int state;
	int left;
	int right;
	int end;
	uint64_t runtime;
	uint64_t currtime;
	bool is_dead;
	bool is_eating;
	t_args args;
	t_status status[5];
	pthread_mutex_t _end;
	pthread_mutex_t *_fork;
	pthread_t id_t;
	// pthread_mutex_t _philo;
};

void init_status(t_philo *philo);
uint64_t get_time(uint64_t *prev);
void _usleep(uint64_t time_in_ms);
void log_msg(t_philo *philo, enum e_state state);
bool is_finished(t_philo *philo);
bool is_dead(t_philo *philo);
void init_philo(t_philo *philo, t_args a);

#endif
