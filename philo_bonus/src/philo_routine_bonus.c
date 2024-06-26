/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:53:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 13:34:14 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static char	*get_unique_sem_name(t_philo *philo, char *name)
{
	char	*sem_name;
	char	*id_str;

	id_str = ft_utoa(philo->id);
	sem_name = ft_strjoin(name, id_str);
	free(id_str);
	return (sem_name);
}

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->time_last_ate = calc_elapsed_ms(data->start_time);
	philo->times_eaten = 0;
	philo->sem_state_name = get_unique_sem_name(philo, "state");
	sem_unlink(philo->sem_state_name);
	philo->sem_state = sem_open(philo->sem_state_name, O_CREAT, 0660, 1);
	philo->data = data;
}

static void	*self_monitor(void *arg)
{
	t_philo	*philo;
	int		current_timestamp;
	int		time_hungry;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->sem_state);
		current_timestamp = calc_elapsed_ms(philo->data->start_time);
		time_hungry = current_timestamp - philo->time_last_ate;
		if (time_hungry > philo->data->time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%d %d died\n", current_timestamp, philo->id);
			sem_post(philo->data->sem_death);
			break ;
		}
		sem_post(philo->sem_state);
		usleep(500);
	}
	return (NULL);
}

void	philo_routine(t_data *data, int i)
{
	t_philo	philo;

	init_philo(&philo, data, i);
	pthread_create(&philo.self_monitor, NULL, self_monitor, (void *)&philo);
	pthread_detach(philo.self_monitor);
	if (philo.data->num_philos == 1)
	{
		print_action(&philo, TAKE_FORK);
		ft_usleep(philo.data->time_to_die * 1000);
	}
	if (philo.id % 2 == 0)
		thinking(&philo);
	while (true)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
}
