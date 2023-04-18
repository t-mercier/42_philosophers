/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _philo.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 09:42:53 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 21:13:47 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

* ARGS
	./philo 4 410 200 200
			+-------------- philo_nb
				+---------- time_die
					+------ time_eat
						+-- time_slp
 
 */

#ifndef _PHILO_H
# define _PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define LEFT 0;
# define RIGHT 1;

typedef struct s_philo	t_philo;
typedef struct s_status	t_status;
typedef struct s_data	t_data;
typedef struct s_fork	t_fork;
typedef struct s_mutex	t_mutex;

enum					e_state
{
	FORKS,
	EAT,
	SLEEP,
	THINK,
	DIE,
	FULL,
	RELEASE,
	SIZE
};

enum					e_mutex
{
	STOP,
	COUNT,
	TIME,
	N,
};

struct					s_mutex
{
	enum e_mutex		mutex_id;
	pthread_mutex_t		mutex;
};

struct					s_fork
{
	int					id;
	pthread_mutex_t		mutex;
};

struct					s_status
{
	enum e_state		flag;
	const char			*msg;
	const char			*c;
};

struct					s_data
{
	uint64_t			t_die;
	uint64_t			t_eat;
	uint64_t			t_sleep;
	uint64_t			time_stamp;
	int					must_eat;
	int					total;
	int					full_count;
	int				stop;
	int					error;
	t_mutex				lock[N];
	pthread_t			*philos_thread;
	pthread_t			watcher;
};

struct					s_philo
{
	t_status			status[SIZE];
	int					id;
	int					eat_count;
	t_fork				*right;
	t_fork				*left;
	uint64_t			last_meal;
	t_data				*data;
};

// actions.c
int						crash(t_philo *philo);
int						eat(t_philo *philo);
int						forks(t_philo *philo);

// check.c
int						game_over(t_philo *philo);
int						is_full(t_philo *philo);
int						is_dead(t_philo *philo);
int						all_stuffed(t_philo *philo, int full);

// log.c
void					log_die(t_philo *philo);
void					log_state(t_philo *philo, int state);
void					status(t_philo *philo);

// mutexes.
int						initialize_mutexes(t_data *data);
int						clean_mutexes(t_fork *fork, t_data *data);

// threads.
void					*cycle(void *arg);
void					*monitor(void *arg);

// time.c
void					_sleep(t_philo *philo, uint64_t time);
uint64_t				get_time_ms(void);
uint64_t				current_time_ms(t_philo *philo);
void					delay(uint64_t time);

// utils.c
void					free_memory(t_philo *philo, t_data *data);
void					*ft_malloc(size_t size);
void					parse_args(int ac, char **av, t_data *data);
int						error(char *s);

static inline int	lock_right(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->right->mutex));
}

static inline int	unlock_right(t_philo *philo)
{
	return (pthread_mutex_unlock(&philo->right->mutex));
}

static inline int	lock_left(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->left->mutex));
}

static inline int	unlock_left(t_philo *philo)
{
	return (pthread_mutex_unlock(&philo->left->mutex));
}

static inline int	lock_time(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->data->lock[TIME].mutex));
}

#endif
