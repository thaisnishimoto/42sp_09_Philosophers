/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 17:26:57 by tmina-ni         ###   ########.fr       */
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
		philo[i].time_last_ate = calc_elapsed_ms(philo->data->start_time);
	philo_threads = malloc(philo->data->num_philos * sizeof(pthread_t));
	if (philo_threads == NULL)
		return ;
	i = -1;
	while (++i < philo->data->num_philos)
		pthread_create(&philo_threads[i], NULL, philo_routine, (void *)&philo[i]);
	pthread_create(&monitoring, NULL, monitor_philos_state, (void *)philo);
	i = -1;
	while (++i < philo->data->num_philos)
		pthread_join(philo_threads[i], NULL);
	pthread_join(monitoring, NULL);
	free(philo_threads);
}

void	*philo_routine(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_action(philo, TAKE_FORK);
		ft_usleep(philo->data->time_to_die * 1000);
		while (!stop_simulation(philo, 0))
			;
		return (NULL);
	}
	while (!stop_simulation(philo, 0))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor_philos_state(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!stop_simulation(philo, 0))
	{
		if (philo_starved(philo))
			stop_simulation(philo, 1);
		if (philo->data->times_must_eat > 0 && all_philos_full(philo))
			stop_simulation(philo, 1);
		usleep(500);
	}
	return (NULL);
}

int	print_action(t_philo *philo, t_philo_action action)
{
	int	timestamp_ms;
	
	pthread_mutex_lock(&philo->data->print_mtx);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (!stop_simulation(philo, 0))
	{
		if (action == TAKE_FORK)
			printf("%d %d has taken a fork\n", timestamp_ms, philo->id);
		else if (action == EAT)
			printf("%d %d is eating\n", timestamp_ms, philo->id);
		else if (action == SLEEP)
			printf("%d %d is sleeping\n", timestamp_ms, philo->id);
		else if (action == THINK)
			printf("%d %d is thinking\n", timestamp_ms, philo->id);
		else if (action == DIE)
			printf("%d %d died\n", timestamp_ms, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print_mtx);
	return (timestamp_ms);
}

bool	stop_simulation(t_philo *philo, int stop)
{
	bool	status;

	pthread_mutex_lock(&philo->data->sim_status_mtx);
	if (stop)
		philo->data->end_sim = true;
	status = philo->data->end_sim;
	pthread_mutex_unlock(&philo->data->sim_status_mtx);
	return (status);
}
