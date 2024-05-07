/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/07 00:15:55 by tmina-ni         ###   ########.fr       */
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
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_must_eat)
		set_philo_full(philo);
	ft_usleep(philo->data->time_to_eat * 1000);
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
