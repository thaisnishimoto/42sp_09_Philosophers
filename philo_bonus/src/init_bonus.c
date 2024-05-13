/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:35 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 13:29:13 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static	int	open_shared_semaphores(t_data *data)
{
	data->sem_fork = sem_open("/fork", O_CREAT, 0660, data->num_philos);
	if (data->sem_fork == SEM_FAILED)
		return (1);
	data->sem_table = sem_open("/table", O_CREAT, 0660, data->num_philos - 1);
	if (data->sem_table == SEM_FAILED)
		return (2);
	data->sem_print = sem_open("/print", O_CREAT, 0660, 1);
	if (data->sem_print == SEM_FAILED)
		return (3);
	data->sem_death = sem_open("/dead", O_CREAT, 0660, 0);
	if (data->sem_death == SEM_FAILED)
		return (4);
	data->sem_full = sem_open("/full", O_CREAT, 0660, 0);
	if (data->sem_full == SEM_FAILED)
		return (5);
	data->sem_stop = sem_open("/stop", O_CREAT, 0660, 1);
	if (data->sem_stop == SEM_FAILED)
		return (6);
	return (0);
}

static void	handle_sem_error(t_data *data, int stage)
{
	if (stage >= 2)
	{
		sem_close(data->sem_fork);
		if (stage >= 3)
		{
			sem_close(data->sem_table);
			if (stage >= 4)
			{
				sem_close(data->sem_print);
				if (stage >= 5)
				{
					sem_close(data->sem_death);
					if (stage >= 6)
						sem_close(data->sem_full);
				}
			}
		}
	}
}

void	init_data(int argc, char *argv[], t_data *data)
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
	data->philo_pid = malloc(data->num_philos * sizeof(int));
	if (data->philo_pid == NULL)
		exit(MALLOC_ERROR);
	unlink_shared_semaphores();
	stage = open_shared_semaphores(data);
	if (stage > 0)
	{
		handle_sem_error(data, stage);
		unlink_shared_semaphores();
		free(data->philo_pid);
		exit(SEM_ERROR);
	}
	data->sim_stop = false;
	data->start_time = get_current_time_ms();
}
