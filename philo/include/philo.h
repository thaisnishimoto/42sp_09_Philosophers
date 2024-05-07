/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:52:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/06 17:26:18 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <unistd.h>
#include <sys/time.h> //gettimeofday
#include <limits.h>
#include <stdbool.h>

#define INPUT_ERROR 1
#define MALLOC_ERROR 2
#define MTX_ERROR 3

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_philo_action;

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	time_ate_mtx;
	pthread_mutex_t	philos_full_mtx;
	pthread_mutex_t	sim_status_mtx;
	bool	end_sim;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	int	id;
	int	time_last_ate;
	int	times_eaten;
	bool	full;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data	*data;
}	t_philo;

//Handle arguments functions
bool	valid_arguments(int argc, char *argv[]);
int	ft_atoi(const char *nptr);

//Init functions
int	init_shared_data(int argc, char *argv[], t_data *data);
void	init_philo_data(t_philo *philo, t_data *data);

//Mutex functions
int	init_mutexes(t_data *data);
void	destroy_mutexes(t_data *data, int stage);

//Time functions
int	get_current_time_ms(void);
int	calc_elapsed_usec(int start_time_ms);
int	calc_elapsed_ms(int start_time_ms);
void	ft_usleep(int usec_sleep_time);

//Simulation functions
void	run_simulation(t_philo *philo);
void	*philo_routine(void *arg);
void	*monitor_philos_state(void *arg);
int		print_action(t_philo *philo, t_philo_action action);
bool	stop_simulation(t_philo *philo, int stop);

//Philo routine
void	*eating(t_philo *philo);
void	*sleeping(t_philo *philo);
void	*thinking(t_philo *philo);
void	take_forks(t_philo *philo);
void	set_philo_full(t_philo *philo);

//Monitor routine
bool	all_philos_full(t_philo *philo);
bool	philo_starved(t_philo *philo);

#endif
