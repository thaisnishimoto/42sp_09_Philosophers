/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/29 23:50:04 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_philos_state(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->end_sim)
	{
		if (philo_starved(philo))
			philo->data->end_sim = true;
		if (philo->data->times_must_eat > 0 && all_philos_full(philo))
			philo->data->end_sim = true;
		usleep(1000);
	}
	return (NULL);
}

bool	all_philos_full(t_philo *philo)
{
	bool	full_state;
	int	i;

	full_state = false;
	i = 0;
	while (i < philo->data->num_philos && !philo->data->end_sim)
	{
		if (philo[i].times_eaten >= philo->data->times_must_eat)
			full_state = true;
		else
			full_state = false;
		i++;
	}
	return (full_state);
}

bool	philo_starved(t_philo *philo)
{
	bool	starved_state;
	int	i;
	unsigned long	timestamp_ms;

	starved_state = false;
	i = 0;
	while (i < philo->data->num_philos && !philo->data->end_sim)
	{
		if (calc_elapsed_ms(philo[i].time_last_ate) > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->print_mtx);
			timestamp_ms = calc_elapsed_ms(philo->data->start_time);
			printf("%lu %d died\n", timestamp_ms, philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mtx);
			starved_state = true;
			break ;
		}
		i++;
	}
	return (starved_state);
}
