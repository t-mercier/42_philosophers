/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 09:47:45 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/19 16:12:09 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	f(void)
// {
// 	system("leaks philo");
// }

static int	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total)
	{
		if (pthread_join(data->philos_thread[i++], NULL) < 0)
			return (error(ERR_THREAD_JOIN), -1);
	}
	if (pthread_join(data->watcher, NULL) < 0)
		return (error(ERR_THREAD_JOIN), -1);
	return (0);
}

void		*single(t_philo *philo);

static int	create_philos(t_fork *fork, t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->total)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		status(&philo[i]);
		philo[i].id = i;
		philo[i].last_meal = get_time_ms();
		fork[i] = (t_fork){.id = i};
		if (pthread_mutex_init(&fork[i].mutex, NULL) < 0)
			return (error(ERR_MUTEX), -1);
		philo[i].right = &fork[i];
		philo[i].left = &fork[(i + 1) % data->total];
		if (i == data->total - 1)
			philo[i].left = &fork[0];
		philo[i].data = data;
		if (pthread_create(&data->philos_thread[i], NULL, cycle, &philo[i]) < 0)
			return (error(ERR_THREAD_CREATE), -1);
		i++;
	}
	return (0);
}

static int	start_threads(t_fork *fork, t_data *data, t_philo *philo)
{
	data->philos_thread = malloc(sizeof(pthread_t) * data->total);
	if (!data->philos_thread)
		return (-1);
	if (create_philos(fork, data, philo) < 0)
		return (-1);
	if (pthread_create(&data->watcher, NULL, monitor, philo) < 0)
		return (-1);
	return (0);
}

int	simulation(t_data *data, t_philo *philo)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork) * data->total);
	if (fork == NULL)
		return (free(fork), -1);
	if (initialize_mutexes(data) < 0)
		return (free(fork), -1);
	if (start_threads(fork, data, philo) < 0)
		return (free(fork), -1);
	if ((wait_threads(data)) < 0)
		return (free(fork), -1);
	if (clean_mutexes(fork, data) < 0)
		return (free(fork), -1);
	return (free(fork), 0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (error(ERR_INPUT_ARGS), -1);
	data = (t_data){0};
	parse_args(ac, av, &data);
	if (data.error)
		return (error(ERR_INPUT_DIGIT), -1);
	if (data.total < 1 || data.total > 2000)
		return (error(ERR_DATA), -1);
	philo = ft_malloc(sizeof(t_philo) * data.total);
	if (simulation(&data, philo) < 0)
		return (free_memory(philo, &data), -1);
	free_memory(philo, &data);
	return (0);
}
