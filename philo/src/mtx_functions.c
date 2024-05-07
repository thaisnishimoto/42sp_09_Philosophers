/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:35 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/07 00:14:34 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mtx, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->time_ate_mtx, NULL) != 0)
		return (2);
	if (pthread_mutex_init(&data->philos_full_mtx, NULL) != 0)
		return (3);
	if (pthread_mutex_init(&data->sim_status_mtx, NULL) != 0)
		return (4);
	return (0);
}

void	destroy_mutexes(t_data *data, int stage)
{
	int	i;	

	if (stage >= 2)
	{
		pthread_mutex_destroy(&data->print_mtx);
		if (stage >= 3)
		{
			pthread_mutex_destroy(&data->time_ate_mtx);
			if (stage >= 4)
			{
				pthread_mutex_destroy(&data->philos_full_mtx);
				if (stage == 5)
					pthread_mutex_destroy(&data->sim_status_mtx);
			}
		}
	}
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->fork_mtx[i++]);
	free(data->fork_mtx);
}
