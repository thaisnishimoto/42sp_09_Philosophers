/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/10 18:31:51 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->time_last_ate = calc_elapsed_ms(data->start_time);
	philo->times_eaten = 0;
	philo->alive = true;
	philo->full = false;
	philo->data = data;
}

bool	philo_alive(t_philo *philo)
{
	int	current_timestamp;
	int	time_hungry;

	current_timestamp = calc_elapsed_ms(philo->data->start_time);
	time_hungry = current_timestamp - philo->time_last_ate;
	if (philo->alive && time_hungry > philo->data->time_to_die)
	{
		sem_wait(philo->data->sem_print);
		printf("%d %d died\n", current_timestamp, philo->id);
		sem_post(philo->data->sem_print);
		philo->alive = false;
		sem_post(philo->data->sem_death);
	}
	return (philo->alive);
}

int	philo_routine(t_data *data, int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	init_philo(&philo, data, i);
//	pthread_create(&philo->self_monitor, NULL, monitor_routine, (void *)philo);
//	pthread_detach(philo->self_monitor);
//	if (philo->data->num_philos == 1)
//	{
//		print_action(philo, TAKE_FORK);
//		ft_usleep(philo->data->time_to_die * 1000);
//		while (!stop_simulation(philo, 0))
//			;
//		return (NULL);
//	}
//	while (true)
	while (philo_alive(&philo) == true)
	{
		eating(&philo);
		if (data->times_must_eat > 0 && philo.full)
			break ;
		sleeping(&philo);
		thinking(&philo);
	}
	close_semaphores(data);
	free(data->philo_pid);
	exit(SUCCESS);
}
