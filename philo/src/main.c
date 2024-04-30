/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/30 15:44:31 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	run_simulation(t_philo *philo)
{
	int	i;
	pthread_t	*philo_threads;
	pthread_t	monitoring;

	if (philo->data->times_must_eat == 0)
		return ;
	philo->data->start_time = get_current_time_ms();
	i = -1;
	while (++i < philo->data->num_philos)
		philo[i].time_last_ate = philo->data->start_time;
	philo_threads = malloc(philo->data->num_philos * sizeof(pthread_t));
	i = -1;
	while (++i < philo->data->num_philos)
		pthread_create(&philo_threads[i], NULL, philo_routine, (void *)&philo[i]);
	pthread_create(&monitoring, NULL, monitor_philos_state, (void *)philo);
	i = -1;
	while (++i < philo->data->num_philos)
		pthread_join(philo_threads[i], NULL);
	pthread_join(monitoring, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int	return_value;

	if (!valid_arguments(argc, argv))
		return (INPUT_ERROR);
//	data = malloc(sizeof(t_data));
//	if (data == NULL)
//		return (MALLOC_ERROR);
	return_value = init_shared_data(argc, argv, &data);
	if (return_value != 0)
		return (return_value);
	philo = malloc(data.num_philos * sizeof(t_philo));
	if (philo)
	{
		init_philo_data(philo, &data);
		run_simulation(philo);
		free(philo);
	}
	else
		return_value = MALLOC_ERROR;
	destroy_mutexes(&data, 4);
	free(data.fork_mtx);
//	free(data);
	return (return_value);
}
