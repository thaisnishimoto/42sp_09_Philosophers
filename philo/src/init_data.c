/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:35 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/16 00:30:07 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutexes(t_data *data, int stage)
{
	int	i;	
	
	if (stage >= 2)
	{
		pthread_mutex_destroy(&data->print_mtx);
		if (stage >= 3)
		{
			pthread_mutex_destroy(&data->time_ate_mtx);
			if (stage == 4)
			pthread_mutex_destroy(&data->philos_full_mtx);
		}
	}
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->fork_mtx[i++]);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->fork_mtx[i], NULL) != 0)
		{
			while (--i >= 0)	
				pthread_mutex_destroy(&data->fork_mtx[i]);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mtx, NULL) != 0)
	{
		destroy_mutexes(data, 1);
		return (1);
	}
	if (pthread_mutex_init(&data->time_ate_mtx, NULL) != 0)
	{
		destroy_mutexes(data, 2);
		return (1);
	}
	if (pthread_mutex_init(&data->philos_full_mtx, NULL) != 0)
	{
		destroy_mutexes(data, 3);
		return (1);
	}
	return (0);
}

int	init_shared_data(int argc, char *argv[], t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	data->fork_mtx = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (data->fork_mtx == NULL)
		return (1);
	if (init_mutexes(data) != 0)
	{
		free(data->fork_mtx);
		return (1);
	}
	data->end_sim = FALSE;
	return (0);
}

void	init_philo_data(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].right_fork = &data->fork_mtx[i];
		philo[i].left_fork = &data->fork_mtx[(i + 1) % data->num_philos];
		philo[i].data = data;
		i++;
	}
}
