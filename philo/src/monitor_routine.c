/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 12:00:05 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_hungry(t_philo *philo)
{
	int	current_timestamp;
	int	time_hungry;

	pthread_mutex_lock(&philo->data->time_ate_mtx);
	current_timestamp = calc_elapsed_ms(philo->data->start_time);
	time_hungry = current_timestamp - philo->time_last_ate;
	pthread_mutex_unlock(&philo->data->time_ate_mtx);
	return (time_hungry);
}

static bool	philo_starved(t_philo *philo)
{
	bool	starved_state;
	int	i;

	starved_state = false;
	i = 0;
	while (i < philo->data->num_philos && !stop_simulation(philo, 0))
	{
		if (time_hungry(&philo[i]) > philo->data->time_to_die)
		{
			print_action(&philo[i], DIE);
			starved_state = true;
			break ;
		}
		i++;
	}
	return (starved_state);
}

static bool	philo_full(t_philo *philo)
{
	bool	is_full;

	is_full = false;
	pthread_mutex_lock(&philo->data->philos_full_mtx);
	if (philo->full)
		is_full = true;
	pthread_mutex_unlock(&philo->data->philos_full_mtx);
	return (is_full);
}

static bool	all_philos_full(t_philo *philo)
{
	bool	full_state;
	int	i;
	int	count_philos_full;

	full_state = false;
	i = 0;
	count_philos_full = 0;
	while (i < philo->data->num_philos && !stop_simulation(philo, 0))
	{
		if (philo_full(&philo[i]))
			count_philos_full++;
		i++;
	}
	if (count_philos_full == philo->data->num_philos)
		full_state = true;
	return (full_state);
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
