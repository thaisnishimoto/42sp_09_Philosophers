/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:52:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/02/16 00:30:04 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <unistd.h>
#include <sys/time.h> //gettimeofday

//#define BOLD "\e[1m"
//#define RESET "\e[m"

#define INPUT_ERROR 1
#define MALLOC_ERROR 2

typedef enum	s_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_data
{
	int	num_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int	times_must_eat;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	time_ate_mtx;
	pthread_mutex_t	philos_full_mtx;
	t_bool	end_sim;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	int	id;
	unsigned long	time_last_ate;
	int	times_eaten;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data	*data;
}	t_philo;


int	check_arguments(int argc, char *argv[]);
int	ft_atoi(const char *nptr);

int	init_shared_data(int argc, char *argv[], t_data *data);
void	init_philo_data(t_philo *philo, t_data *data);

unsigned long	get_current_time_ms(void);
unsigned long	calc_elapsed_usec(unsigned long start_time_ms);
unsigned long	calc_elapsed_ms(unsigned long start_time_ms);
void	ft_usleep(unsigned long usec_sleep_time);

void	*sleeping(t_philo *philo);
void	*philo_routine(void *arg);
void	*monitor_philos_full(void *arg);
t_bool	all_philos_full(t_philo *philo);
t_bool	philo_starved(t_philo *philo);
void	destroy_mutexes(t_data *data, int stage);

#endif
