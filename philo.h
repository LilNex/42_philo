

#ifndef PHILO_H
#define PHILO_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_philo{
    int			num;
    pthread_t	thread;

	struct timeval start_date;
	struct timeval last_eaten;

	struct s_config	*config;
}               t_philo;

typedef struct s_config{
	int num_philos;
	int time_sleep;
	int time_eat;
	int time_think;
	struct timeval start_date;
	t_philo **philos;
}           t_config;


// UTILS
void        print_config(t_config *config);
long long get_current_tick(t_config *config, struct timeval time);
void print_log(t_config *config, char *str);



void *philo_routine(void *conf);

// ARGS
int			validate_param(char *str);
void		parse_args(char **args, t_config *config);
int			validate_args(t_config *config);
void		create_philos(t_config *philo);
#endif