/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:56:19 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/07 00:21:03 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_current_time_ms(void)
{
	struct timeval	tv;
	int				time_ms;

	gettimeofday(&tv, NULL);
	time_ms = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time_ms);
}

int	calc_elapsed_ms(int start_time_ms)
{
	int	elapsed_time_ms;

	elapsed_time_ms = get_current_time_ms() - start_time_ms;
	return (elapsed_time_ms);
}

int	calc_elapsed_usec(int start_time_ms)
{
	int	elapsed_time_ms;

	elapsed_time_ms = get_current_time_ms() - start_time_ms;
	return (elapsed_time_ms * 1000);
}

void	ft_usleep(int usec_sleep_time)
{
	int	start_time_ms;
	int	usec_left;

	start_time_ms = get_current_time_ms();
	while ((calc_elapsed_usec(start_time_ms) < usec_sleep_time))
	{
		usec_left = usec_sleep_time - calc_elapsed_usec(start_time_ms);
		if (usec_left > 1000)
			usleep(usec_left / 2);
	}
}
