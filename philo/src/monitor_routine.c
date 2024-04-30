/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/30 18:22:38 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	last_meal_time(t_philo *philo)
{
	int	time_last_ate;

	pthread_mutex_lock(&philo->data->time_ate_mtx);
	time_last_ate = calc_elapsed_ms(philo->time_last_ate);
	pthread_mutex_unlock(&philo->data->time_ate_mtx);
	return (time_last_ate);
}

static bool	philo_starved(t_philo *philo)
{
	bool	starved_state;
	int	i;

	starved_state = false;
	i = 0;
	while (i < philo->data->num_philos && !stop_simulation(philo, 0))
	{
		if (last_meal_time(&philo[i]) > philo->data->time_to_die)
		{
			print_action(&philo[i], DIE);
			starved_state = true;
			break ;
		}
		i++;
	}
	return (starved_state);
}

static bool	all_philos_full(t_philo *philo)
{
	bool	all_full;

	all_full = false;
	pthread_mutex_lock(&philo->data->philos_full_mtx);
	if (philo->data->philos_full == philo->data->num_philos)
		all_full = true;
	pthread_mutex_unlock(&philo->data->philos_full_mtx);
	return (all_full);
}

//static bool	all_philos_full(t_philo *philo)
//{
//	bool	full_state;
//	int	i;
//
//	full_state = false;
//	i = 0;
//	while (i < philo->data->num_philos && !stop_simulation(philo, 0))
//	{
//		if (philo[i].times_eaten >= philo->data->times_must_eat)
//			full_state = true;
//		else
//			full_state = false;
//		i++;
//	}
//	return (full_state);
//}

void	*monitor_philos_state(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!stop_simulation(philo, 0))
	{
		if (philo_starved(philo))
			stop_simulation(philo, 1);
		if (philo->data->times_must_eat >= 1 && all_philos_full(philo))
			stop_simulation(philo, 1);
//		usleep(1000);
	}
	return (NULL);
}
