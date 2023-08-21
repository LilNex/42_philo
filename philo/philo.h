/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:58:04 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/21 21:35:39 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_philo{
	int				num;
	pthread_t		thread;
	struct timeval	start_date;
	struct timeval	last_eaten;
	int				meals_eaten;
	pthread_mutex_t	fork;
	pthread_mutex_t	mut_last_eaten;
	struct s_config	*config;
}					t_philo;

typedef struct s_config{
	int				num_philos;
	int				time_sleep;
	int				time_eat;
	int				time_die;
	int				number_meals;
	int				exit;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	struct timeval	start_date;
	t_philo			**philos;
}					t_config;

void		destroy_config(t_config *config);
void		print_config(t_config *config);
long long	to_ms(struct timeval datetime);
void		print_log(t_philo *philo, char *str);
void		*thread_checker(void *conf);
int			routine_checker(t_philo *philo, struct timeval date_now);
void		philo_sleep(t_philo *philo);
void		take_fork(t_philo *philo);
void		*philo_routine(void *conf);
int			is_all_meals_eaten(t_config *config);
void		ft_exit(char *str);
int			ft_usleep(useconds_t time);
void		destroy_thread(t_philo *philo);
void		lock_all_mutexs(t_config *config);
int			is_exited(t_config *config);

// ARGS
int			validate_param(char *str);
int			parse_args(char **args, t_config *config);
int			validate_args(t_config *config);
void		create_philos(t_config *philo);
int			set_exit(t_config *config, int value);
#endif