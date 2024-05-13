/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 13:44:00 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	int		philos_full;

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

int	main(int argc, char *argv[])
{
	t_data		data;
	int			i;
	pthread_t	monitor_death;
	pthread_t	monitor_full;

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
	pthread_create(&monitor_death, NULL, &death_routine, (void *)&data);
	pthread_create(&monitor_full, NULL, &all_full_routine, (void *)&data);
	pthread_join(monitor_death, NULL);
	pthread_join(monitor_full, NULL);
	wait_finish_philos(&data);
	return (SUCCESS);
}
