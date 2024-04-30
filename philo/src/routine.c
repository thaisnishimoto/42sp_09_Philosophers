/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/30 11:51:46 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	philo_starved(t_philo *philo)
{
	bool	starved_state;
	int	i;

	starved_state = false;
	i = 0;
	while (i < philo->data->num_philos && !philo->data->end_sim)
	{
		if (calc_elapsed_ms(philo[i].time_last_ate) > philo->data->time_to_die)
		{
			print_action(philo, DIE);
			starved_state = true;
			break ;
		}
		i++;
	}
	return (starved_state);
}

static bool	all_philos_full(t_philo *philo)
{
	bool	full_state;
	int	i;

	full_state = false;
	i = 0;
	while (i < philo->data->num_philos && !stop_simulation(philo, 0))
	{
		if (philo[i].times_eaten >= philo->data->times_must_eat)
			full_state = true;
		else
			full_state = false;
		i++;
	}
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
//		usleep(1000);
	}
	return (NULL);
}
