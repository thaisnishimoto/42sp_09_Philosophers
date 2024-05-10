/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:35 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/10 16:01:11 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static	bool	open_semaphores(t_data *data)
{
	data->sem_fork = sem_open("/fork", O_CREAT, 0660, data->num_philos);
	if (data->sem_fork == SEM_FAILED)
		return (false);
	data->sem_table = sem_open("/table", O_CREAT, 0660, data->num_philos - 1);
	if (data->sem_table == SEM_FAILED)
	{
		sem_close(data->sem_fork);
		return (false);
	}
	data->sem_print = sem_open("/print", O_CREAT, 0660, 1);
	if (data->sem_print == SEM_FAILED)
	{
		sem_close(data->sem_fork);
		sem_close(data->sem_table);
		return (false);
	}
	data->sem_death = sem_open("/dead", O_CREAT, 0660, 0);
	if (data->sem_death == SEM_FAILED)
	{
		sem_close(data->sem_fork);
		sem_close(data->sem_table);
		sem_close(data->sem_print);
		return (false);
	}
	return (true);
}

void	init_data(int argc, char *argv[], t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	data->philo_pid = malloc(data->num_philos * sizeof(int));
	if (data->philo_pid == NULL)
		exit(MALLOC_ERROR);
	unlink_semaphores();
	if (!open_semaphores(data))
	{
		free(data->philo_pid);
		unlink_semaphores();
		exit(SEM_ERROR);
	}
	data->start_time = get_current_time_ms();
}
