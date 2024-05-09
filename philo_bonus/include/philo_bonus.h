/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:52:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/09 11:04:16 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h> //malloc
# include <unistd.h> //fork
# include <sys/time.h> //gettimeofday
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h> //waitpid

# define SUCESS 0
# define INPUT_ERROR 1
# define MALLOC_ERROR 2
# define SEM_ERROR 2

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
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pid_t	philo_pid;
	sem_t	*sem_fork;
	sem_t	*sem_table;
	sem_t	*sem_print;
	int				start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				time_last_ate;
	int				times_eaten;
	t_data			*data;
}	t_philo;

//Handle arguments functions
bool	valid_arguments(int argc, char *argv[]);
int		ft_atoi(const char *nptr);

//Init functions
int		init_shared_data(int argc, char *argv[], t_data *data);
void	init_philo_data(t_philo *philo, t_data *data);

//Time functions
int		get_current_time_ms(void);
int		calc_elapsed_usec(int start_time_ms);
int		calc_elapsed_ms(int start_time_ms);
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
