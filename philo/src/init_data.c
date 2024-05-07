/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:35 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 17:24:34 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_shared_data(int argc, char *argv[], t_data *data)
{
	int	stage;

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
		return (MALLOC_ERROR);
	stage = init_mutexes(data);
	if (stage != 0)
	{
		if (stage >= 1)
			destroy_mutexes(data, stage);
		return (MTX_ERROR);
	}
	data->end_sim = false;
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
		philo[i].full = false;
		philo[i].right_fork = &data->fork_mtx[i];
		philo[i].left_fork = &data->fork_mtx[(i + 1) % data->num_philos];
		philo[i].data = data;
		i++;
	}
}
