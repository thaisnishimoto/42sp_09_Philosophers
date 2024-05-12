/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/11 23:38:47 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*self_monitor(void *arg)
{
	t_philo	*philo;
	int	current_timestamp;
	int	time_hungry;

	philo = (t_philo *)arg;
	while (philo_is_alive(philo, 0))
	{
		current_timestamp = calc_elapsed_ms(philo->data->start_time);
		time_hungry = current_timestamp - philo->time_last_ate;
 		if (time_hungry > philo->data->time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%d %d died\n", current_timestamp, philo->id);
			sem_post(philo->data->sem_print);
			philo_is_alive(philo, 1);
			sem_post(philo->data->sem_death);
		}
		usleep(500);
	}
	return (NULL);
}

char	*get_unique_sem_name(t_philo *philo)
{
	char	*sem_name;
	char	*id_str;

	id_str = ft_utoa(philo->id);
	sem_name = ft_strjoin("state", id_str);
	free(id_str);
	return (sem_name);
}

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->time_last_ate = calc_elapsed_ms(data->start_time);
	philo->times_eaten = 0;
	philo->alive = true;
	philo->full = false;
	philo->sem_state_name = get_unique_sem_name(philo);
	sem_unlink(philo->sem_state_name);
	philo->sem_state = sem_open(philo->sem_state_name, O_CREAT, 0660, 1);
	philo->data = data;
}

bool	philo_is_alive(t_philo *philo, int died)
{
	bool	state;

	sem_wait(philo->sem_state);
	if (died)
		philo->alive = false;	
	state = philo->alive;	
	sem_post(philo->sem_state);
	return (state);
}

static void	finish_child(t_philo *philo)
{
	sem_close(philo->sem_state);
	sem_unlink(philo->sem_state_name);
	free(philo->sem_state_name);
	close_shared_semaphores(philo->data);
	free(philo->data->philo_pid);
}

int	philo_routine(t_data *data, int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	init_philo(&philo, data, i);
	pthread_create(&philo.self_monitor, NULL, self_monitor, (void *)&philo);
	pthread_detach(philo.self_monitor);
//	if (philo->data->num_philos == 1)
//	{
//		print_action(philo, TAKE_FORK);
//		ft_usleep(philo->data->time_to_die * 1000);
//		while (!stop_simulation(philo, 0))
//			;
//		return (NULL);
//	}
	while (true)
//	while (philo_is_alive(&philo, 0))
	{
		eating(&philo);
		if (data->times_must_eat > 0 && philo.full)
		{
			finish_child(&philo);
			exit(PHILO_FULL);
		}	
		sleeping(&philo);
		thinking(&philo);
	}
	finish_child(&philo);
//	sem_wait(philo.data->sem_print);
	printf("%d exiting  philo\n", philo.id);
//	sem_post(philo.data->sem_print);
	exit(PHILO_DEAD);
}