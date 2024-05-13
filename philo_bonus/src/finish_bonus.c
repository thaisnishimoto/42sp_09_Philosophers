/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 10:54:23 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	simulation_stopped(t_data *data, int stop)
{
	bool	state;

	sem_wait(data->sem_stop);
	if (stop)
		data->sim_stop = true;
	state = data->sim_stop;
	sem_post(data->sem_stop);
	return (state);
}

void	kill_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philo_pid[i], SIGKILL);
		i++;
	}
}

void	*death_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->sem_death);
	if (simulation_stopped(data, 0))
		return (NULL);
	simulation_stopped(data, 1);
	kill_all_philos(data);
	sem_post(data->sem_full);
	return (NULL);
}

void	*all_full_routine(void *arg)
{
	t_data	*data;
	int	philos_full;

	data = (t_data *)arg;
	philos_full = 0;
	while (philos_full < data->num_philos)
	{
		sem_wait(data->sem_full);
		if (simulation_stopped(data, 0))
			return (NULL);
		philos_full++;
	}
	simulation_stopped(data, 1);
	kill_all_philos(data);
	sem_post(data->sem_death);
	return (NULL);
}

//void	*kill_all_philos(void *arg)
//{
//	t_data	*data;
//	int	i;
//
//	data = (t_data *)arg;
//	sem_wait(data->sem_death);
//	i = 0;
//	while (i < data->num_philos)
//	{
//		kill(data->philo_pid[i], SIGKILL);
//		i++;
//	}
//	return (NULL);
//}

void	wait_finish_philos(t_data *data)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
		;
	close_shared_semaphores(data);
	unlink_shared_semaphores();
	free(data->philo_pid);
}
//void	wait_finish_philos(t_data *data)
//{
//	int	status;
//	int	philos_full;
//
//	philos_full = 0;
//	while (waitpid(-1, &status, 0) != -1)
//	{
//		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
//			philos_full++;
//	}
//	if (philos_full == data->num_philos)
//	{
//		printf("all full\n");
//		kill_all_philos(data);
//		//;
//	}
//	close_shared_semaphores(data);
//	unlink_shared_semaphores();
//	free(data->philo_pid);
//}

void	close_shared_semaphores(t_data *data)
{
	sem_close(data->sem_fork);
	sem_close(data->sem_table);
	sem_close(data->sem_print);
	sem_close(data->sem_death);
	sem_close(data->sem_full);
	sem_close(data->sem_stop);
}

void	unlink_shared_semaphores(void)
{
	sem_unlink("/fork");
	sem_unlink("/table");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/full");
	sem_unlink("/stop");
}
