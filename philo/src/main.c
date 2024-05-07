/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/07 00:12:22 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int		return_value;

	if (!valid_arguments(argc, argv))
		return (INPUT_ERROR);
	return_value = init_shared_data(argc, argv, &data);
	if (return_value != 0)
		return (return_value);
	philo = malloc(data.num_philos * sizeof(t_philo));
	if (philo)
	{
		init_philo_data(philo, &data);
		run_simulation(philo);
		free(philo);
	}
	else
		return_value = MALLOC_ERROR;
	destroy_mutexes(&data, 5);
	return (return_value);
}
