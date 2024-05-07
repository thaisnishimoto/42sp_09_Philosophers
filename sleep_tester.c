/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:27 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/08 15:28:11 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	unsigned long	start;
	double	elapsed;
	double	ft_elapsed;

	start = get_current_time_ms(); 
	usleep(500000);
	elapsed = calc_elapsed_usec(start) / 1000000.0; 
	start = get_current_time_ms(); 
	ft_usleep(500000);
	ft_elapsed = calc_elapsed_usec(start) / 1000000.0; 
	printf("Expected sleep duration: 0.5 seconds\n");
	printf("usleep duration: %.6f seconds\n", elapsed);
	printf("ft_usleep duration: %.6f seconds\n", ft_elapsed);
	return (0);
}
