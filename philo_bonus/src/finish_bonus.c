/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/10 17:49:30 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *)arg;
	sem_wait(data->sem_death);
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philo_pid[i], SIGKILL);
		i++;
	}
	return (NULL);
}

void	wait_free_philos(t_data *data)
{
	int	i;
	int	status;
//	int	philos_full;

	i = 0;
//	philos_full = 0;
	while (i < data->num_philos)
	{
		waitpid(0, &status, 0);
//		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
//			philos_full++;
		i++;
	}
	close_semaphores(data);
	unlink_semaphores();
	free(data->philo_pid);
//	if (data->times_must_eat > 0 &&)
}

void	close_semaphores(t_data *data)
{
	sem_close(data->sem_fork);
	sem_close(data->sem_table);
	sem_close(data->sem_print);
	sem_close(data->sem_death);
}

void	unlink_semaphores(void)
{
	sem_unlink("/fork");
	sem_unlink("/table");
	sem_unlink("/print");
	sem_unlink("/dead");
}
