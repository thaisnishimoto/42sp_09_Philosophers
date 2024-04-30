/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/04/29 17:46:43 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	end_simulation(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->data->sim_status_mtx);
	status = philo->data->end_sim;
	pthread_mutex_unlock(&philo->data->sim_status_mtx);
	return (status);
}

void	print_action(t_philo *philo, t_philo_action action)
{
	int	timestamp_ms;
	
	pthread_mutex_lock(&philo->data->print_mtx);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (!end_simulation(philo))
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

}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time_ate_mtx);
	philo->time_last_ate = get_current_time_ms();
	pthread_mutex_unlock(&philo->data->time_ate_mtx);
}

void	update_philos_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos_full_mtx);
	philo->data->philos_full++;
	pthread_mutex_unlock(&philo->data->philos_full_mtx);
}

static void	take_forks(t_philo *philo)
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

static void	*eating(t_philo *philo)
{
	take_forks(philo);
	print_action(philo, EAT);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_must_eat)
		update_philos_full(philo);
	update_meal_time(philo);
	ft_usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	*sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}

static void	*thinking(t_philo *philo)
{
	print_action(philo, THINK);
	return (NULL);
}

void	*philo_routine(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!end_simulation(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
