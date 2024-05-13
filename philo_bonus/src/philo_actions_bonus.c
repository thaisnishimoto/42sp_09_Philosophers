/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 13:14:07 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_table);
	sem_wait(philo->data->sem_fork);
	print_action(philo, TAKE_FORK);
	sem_wait(philo->data->sem_fork);
	print_action(philo, TAKE_FORK);
	sem_post(philo->data->sem_table);
}

void	eating(t_philo *philo)
{
	int	action_timestamp;

	take_forks(philo);
	sem_wait(philo->sem_state);
	action_timestamp = print_action(philo, EAT);
	philo->time_last_ate = action_timestamp;
	sem_post(philo->sem_state);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_must_eat)
		sem_post(philo->data->sem_full);
	ft_usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(500);
}

int	print_action(t_philo *philo, t_philo_action action)
{
	int	timestamp_ms;

	sem_wait(philo->data->sem_print);
	timestamp_ms = calc_elapsed_ms(philo->data->start_time);
	if (action == TAKE_FORK)
		printf("%d %d has taken a fork\n", timestamp_ms, philo->id);
	else if (action == EAT)
		printf("%d %d is eating\n", timestamp_ms, philo->id);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", timestamp_ms, philo->id);
	else if (action == THINK)
		printf("%d %d is thinking\n", timestamp_ms, philo->id);
	sem_post(philo->data->sem_print);
	return (timestamp_ms);
}

