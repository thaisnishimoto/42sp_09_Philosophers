/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/15 19:57:08 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	unsigned long	timestamp_ms;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print_mtx);
		timestamp_ms = calc_elapsed_ms(philo->data->start_time);
		if (!philo->data->end_sim)
			printf("%lu %d has taken a fork\n", timestamp_ms, philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print_mtx);
		timestamp_ms = calc_elapsed_ms(philo->data->start_time);
		if (!philo->data->end_sim)
			printf("%lu %d has taken a fork\n", timestamp_ms, philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
	else	
	{
	      	pthread_mutex_lock(philo->right_fork);
	      	pthread_mutex_lock(&philo->data->print_mtx);
	      	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
		if (!philo->data->end_sim)
	      		printf("%lu %d has taken a fork\n", timestamp_ms, philo->id);
	      	pthread_mutex_unlock(&philo->data->print_mtx);
	      	pthread_mutex_lock(philo->left_fork);
	      	pthread_mutex_lock(&philo->data->print_mtx);
	      	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
		if (!philo->data->end_sim)
	      		printf("%lu %d has taken a fork\n", timestamp_ms, philo->id);
	      	pthread_mutex_unlock(&philo->data->print_mtx);
	}
}

void	*eating(t_philo *philo)
{
	unsigned long	timestamp_ms;

	take_forks(philo);
	pthread_mutex_lock(&philo->data->print_mtx);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (!philo->data->end_sim)
		printf("%lu %d is eating\n", timestamp_ms, philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	philo->times_eaten++;
	philo->time_last_ate = get_current_time_ms();
	ft_usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
//	if (philo->times_eaten == philo->data->times_must_eat)
//	{
//		pthread_mutex_lock(&philo->data->philos_full_mtx);
//		philo->data->philos_full++;
//		pthread_mutex_unlock(&philo->data->philos_full_mtx);
//	}
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	unsigned long	timestamp_ms;

	pthread_mutex_lock(&philo->data->print_mtx);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (!philo->data->end_sim)
		printf("%lu %d is sleeping\n", timestamp_ms, philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	ft_usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	unsigned long	timestamp_ms;

	pthread_mutex_lock(&philo->data->print_mtx);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (!philo->data->end_sim)
		printf("%lu %d is thinking\n", timestamp_ms, philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	return (NULL);
}

void	*philo_routine(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->end_sim)
	{
		if (!philo->data->end_sim)
			eating(philo);
		if (!philo->data->end_sim)
			sleeping(philo);
		if (!philo->data->end_sim)
			thinking(philo);
	}
	return (NULL);
}

void	*monitor_philos_full(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->end_sim)
	{
		if (philo_starved(philo))
			philo->data->end_sim = TRUE;
		if (philo->data->times_must_eat > 0 && all_philos_full(philo))
			philo->data->end_sim = TRUE;
		usleep(1000);
	}
	return (NULL);
}

t_bool	all_philos_full(t_philo *philo)
{
	t_bool	full_state;
	int	i;

	full_state = FALSE;
	i = 0;
	while (i < philo->data->num_philos && !philo->data->end_sim)
	{
		if (philo[i].times_eaten >= philo->data->times_must_eat)
			full_state = TRUE;
		else
			full_state = FALSE;
		i++;
	}
	return (full_state);
}

t_bool	philo_starved(t_philo *philo)
{
	t_bool	starved_state;
	int	i;
	unsigned long	timestamp_ms;

	starved_state = FALSE;
	i = 0;
	while (i < philo->data->num_philos && !philo->data->end_sim)
	{
		if (calc_elapsed_ms(philo[i].time_last_ate) > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->print_mtx);
			timestamp_ms = calc_elapsed_ms(philo->data->start_time);
			printf("%lu %d died\n", timestamp_ms, philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mtx);
			starved_state = TRUE;
			break ;
		}
		i++;
	}
	return (starved_state);
}
