/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 15:37:50 by tmercier      #+#    #+#                 */
/*   Updated: 2023/04/17 20:46:22 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *s)
{
	return (printf("%s%s\n", RED, s));
}

void	free_memory(t_philo *philo, t_data *data)
{
	if (philo)
		free(philo);
	if (data->philos_thread != NULL)
		free(data->philos_thread);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (error(ERR_MALLOC), NULL);
	return (ptr);
}

uint64_t	get_args(const char *str, t_data *data)
{
	int	res;

	res = 0;
	if (!*str || *str == '-' || *str == '+')
	{
		data->error = 1;
		return (-1);
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			if (res > (INT_MAX - (*str - '0')) / 10)
				data->error = 1;
			res = res * 10 + (*str - '0');
		}
		if (res < 1)
			data->error = 1;
		str++;
	}
	return ((uint64_t)res);
}

void	parse_args(int ac, char **av, t_data *data)
{
	data->total = get_args(av[1], data);
	data->t_die = get_args(av[2], data);
	data->t_eat = get_args(av[3], data);
	data->t_sleep = get_args(av[4], data);
	data->must_eat = -1;
	if (ac == 6)
	{
		data->must_eat = get_args(av[5], data);
		if (data->must_eat < 1)
			data->error = 1;
	}
}
