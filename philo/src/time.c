/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:56:19 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/10 01:03:46 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_current_time_ms(void)
{
	struct timeval	tv;
	int	time_ms;

	gettimeofday(&tv, NULL);
	time_ms = ((tv.tv_sec * 1000) + (tv.tv_usec/ 1000));
	return (time_ms);
}

unsigned long	calc_elapsed_ms(unsigned long start_time_ms)
{
	unsigned long	elapsed_time_ms;

	elapsed_time_ms = get_current_time_ms() - start_time_ms;
	return (elapsed_time_ms);
}

unsigned long	calc_elapsed_usec(unsigned long start_time_ms)
{
	unsigned long	elapsed_time_ms;

	elapsed_time_ms = get_current_time_ms() - start_time_ms;
	return (elapsed_time_ms * 1000);
}

void	ft_usleep(unsigned long usec_sleep_time)
{
	unsigned long	start_time_ms;
	unsigned long	usec_left;

	start_time_ms = get_current_time_ms();
	while ((calc_elapsed_usec(start_time_ms) < usec_sleep_time))
	{
		usec_left = usec_sleep_time - calc_elapsed_usec(start_time_ms);
		if (usec_left > 1000)
			usleep(usec_left / 2);
	}
}
