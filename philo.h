

#ifndef PHILO_H

# define PHILO_H



# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct s_philo{
	int				num;
	pthread_t		thread;
	struct timeval	start_date;
	struct timeval	last_eaten;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	mut_last_eaten;
	struct s_config	*config;
}					t_philo;

typedef struct s_config{
	int				num_philos;
	int				time_sleep;
	int				time_eat;
	int				time_die;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	int				died;
	struct timeval	start_date;
	t_philo			**philos;
}					t_config;


// UTILS
void		print_config(t_config *config);
long long	to_ms(struct timeval datetime);
void		print_log(t_philo *philo, char *str);
void		*thread_checker(void *conf);


void		philo_sleep(t_philo *philo);
void		take_fork(t_philo *philo);
void		*philo_routine(void *conf);
void		ft_exit(char *str);

int			ft_usleep(useconds_t time);

// ARGS
int			validate_param(char *str);
void		parse_args(char **args, t_config *config);
int			validate_args(t_config *config);
void		create_philos(t_config *philo);
#endif