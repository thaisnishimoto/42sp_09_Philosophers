/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:52:07 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 01:57:27 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h> //malloc
# include <unistd.h> //fork
# include <sys/time.h> //gettimeofday
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h> //waitpid
# include <string.h> //memset

# define SUCCESS 0
# define INPUT_ERROR 1
# define MALLOC_ERROR 2
# define SEM_ERROR 3
# define FORK_ERROR 4

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
}	t_philo_action;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pid_t	*philo_pid;
	sem_t	*sem_fork;
	sem_t	*sem_table;
	sem_t	*sem_print;
	sem_t	*sem_death;
	sem_t	*sem_stop_sim;
	int				start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				time_last_ate;
	int				times_eaten;
	bool	full;
	pthread_t	self_monitor;
	char	*sem_state_name;
	sem_t	*sem_state;
	t_data			*data;
}	t_philo;

//Handle arguments functions
bool	valid_arguments(int argc, char *argv[]);
int		ft_atoi(const char *nptr);

//Init function
void	init_data(int argc, char *argv[], t_data *data);

//Time functions
int		get_current_time_ms(void);
int		calc_elapsed_usec(int start_time_ms);
int		calc_elapsed_ms(int start_time_ms);
void	ft_usleep(int usec_sleep_time);

//Philo routine
int		philo_routine(t_data *data, int i);

//Philo actions
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
int		print_action(t_philo *philo, t_philo_action action);

//Utils
pid_t	ft_fork(t_data *data);
char	*ft_utoa(unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);

//Finish functions
void	*kill_all_philos(void *arg);
void	wait_finish_philos(t_data *data);
void	close_shared_semaphores(t_data *data);
void	unlink_shared_semaphores(void);

#endif
