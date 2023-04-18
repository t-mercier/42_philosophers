/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 15:58:15 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 20:48:02 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "_philo.h"

# define ERR_INPUT_ARGS "error usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define ERR_INPUT_DIGIT "error input: \
enter a valid unsigned integer between 1 and 2147483647.\n"
# define ERR_DATA "error: invalid number of philosophers.\n"
# define ERR_THREAD_CREATE "error: Could not create thread.\n"
# define ERR_THREAD_JOIN "error: Could not join thread.\n"
# define ERR_MALLOC "error: Could not allocate memory.\n"
# define ERR_MUTEX "error: Could not create mutex.\n"
# define ERR_PARSING "error: Could not find any string to parse.\n"

# define PURPLE "\x1b[35m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define CYAN "\x1b[36m"

static inline int	lock_stop(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->data->lock[STOP].mutex));
}

static inline int	unlock_stop(t_philo *philo)
{
	return (pthread_mutex_unlock(&philo->data->lock[STOP].mutex));
}

static inline int	lock_count(t_philo *philo)
{
	return (pthread_mutex_lock(&philo->data->lock[COUNT].mutex));
}

static inline int	unlock_count(t_philo *philo)
{
	return (pthread_mutex_unlock(&philo->data->lock[COUNT].mutex));
}

static inline int	unlock_time(t_philo *philo)
{
	return (pthread_mutex_unlock(&philo->data->lock[TIME].mutex));
}

#endif
