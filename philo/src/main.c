/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/24 16:17:25 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	run_threads(t_philo *philo)
{
	int	i;
	pthread_t	*philo_threads;
	pthread_t	monitoring;

	philo->data->start_time = get_current_time_ms();
	i = 0;
	while (i < philo->data->num_philos)
	{
		philo[i].time_last_ate = philo->data->start_time;
		i++;
	}
	philo_threads = malloc(philo->data->num_philos * sizeof(pthread_t));
	i = 0;
	while (i < philo->data->num_philos)
	{
		pthread_create(&philo_threads[i], NULL, philo_routine, (void *)&philo[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, monitor_philos_full, (void *)philo);
	i = 0;
	while (i < philo->data->num_philos)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	pthread_join(monitoring, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;

	if (check_arguments(argc, argv) != 0)
		return (INPUT_ERROR);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (MALLOC_ERROR);
	init_shared_data(argc, argv, data);
	philo = malloc(data->num_philos * sizeof(t_philo));
	if (philo == NULL)
	{
		destroy_mutexes(data, 4);
		free(data->fork_mtx);
		free(data);
		return (MALLOC_ERROR);
	}
	init_philo_data(philo, data);
	run_threads(philo);
	destroy_mutexes(data, 4);
	free(data->fork_mtx);
	free(data);
	free(philo);
	return (0);
}
