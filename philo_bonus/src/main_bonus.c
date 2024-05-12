/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/11 22:59:08 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->sem_death);
	kill_all_philos(data);
	return (NULL);
}

static pid_t	ft_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close_shared_semaphores(data);
		unlink_shared_semaphores();
		free(data->philo_pid);
		exit(FORK_ERROR);
	}
	return (pid);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	pthread_t	monitor;

	if (!valid_arguments(argc, argv))
		return (INPUT_ERROR);
	init_data(argc, argv, &data);
	i = 0;
	while (i < data.num_philos)
	{
		data.philo_pid[i] = ft_fork(&data);
		if (data.philo_pid[i] == 0)
			philo_routine(&data, i);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_death, (void *)&data);
	pthread_detach(monitor);
	wait_free_philos(&data);
	return (SUCCESS);
}
