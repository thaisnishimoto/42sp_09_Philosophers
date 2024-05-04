/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/03 19:35:31 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	print_action(t_philo *philo, t_philo_action action)

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

//void	update_meal_time(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->data->time_ate_mtx);
//	philo->time_last_ate = get_current_time_ms();
//	pthread_mutex_unlock(&philo->data->time_ate_mtx);
//}

void	set_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos_full_mtx);
	philo->full = true;
	pthread_mutex_unlock(&philo->data->philos_full_mtx);
}
