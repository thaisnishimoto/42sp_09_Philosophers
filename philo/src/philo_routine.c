/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 17:06:43 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*eating(t_philo *philo)
{
	int	action_timestamp;

	take_forks(philo);
	pthread_mutex_lock(&philo->data->time_ate_mtx);
	action_timestamp = print_action(philo, EAT);
	philo->time_last_ate = action_timestamp;
	pthread_mutex_unlock(&philo->data->time_ate_mtx);
	ft_usleep(philo->data->time_to_eat * 1000);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_must_eat)
		set_philo_full(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
	}
	else	
	{
	      	pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
	      	pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
	}
}

void	set_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos_full_mtx);
	philo->full = true;
	pthread_mutex_unlock(&philo->data->philos_full_mtx);
}

void	*sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(500);
	return (NULL);
}

//void	*philo_routine(void* arg)
//{
//	t_philo	*philo;
//
//	philo = (t_philo *)arg;
//	if (philo->data->num_philos == 1)
//	{
//		print_action(philo, TAKE_FORK);
//		ft_usleep(philo->data->time_to_die * 1000);
//		while (!stop_simulation(philo, 0))
//			;
//		return (NULL);
//	}
//	while (!stop_simulation(philo, 0))
//	{
//		eating(philo);
//		sleeping(philo);
//		thinking(philo);
//	}
//	return (NULL);
//}
