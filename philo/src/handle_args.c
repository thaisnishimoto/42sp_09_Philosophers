/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:31:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 17:28:13 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	unsigned char	i;
	int				sign;
	int				num;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	sign = 1;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if ((nptr[i] != '\0') && (nptr[i] < '0' || nptr[i] > '9'))
		return (-1);
	return (sign * num);
}

bool	valid_arguments(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[times_each_must_eat]\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > INT_MAX)
		{
			printf("Error: argv[%d] must be a positive integer\n", i);
			return (false);
		}
		i++;
	}
	return (true);
}
