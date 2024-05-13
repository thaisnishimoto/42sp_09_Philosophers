/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/12 19:24:06 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	pthread_t	monitor_death;

	if (!valid_arguments(argc, argv))
		return (INPUT_ERROR);
	init_data(argc, argv, &data);
	i = 0;
	while (i < data.num_philos)
	{
		data.philo_pid[i] = ft_fork(&data);
		if (data.philo_pid[i] == 0)
			philo_routine(&data, i);
		i++;
	}
	pthread_create(&monitor_death, NULL, &kill_all_philos, (void *)&data);
	pthread_detach(monitor_death);
	wait_finish_philos(&data);
	return (SUCCESS);
}
