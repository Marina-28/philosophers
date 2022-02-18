#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    int					numb_of_ph;
    int					time_to_die;
    int					time_to_eat;
    int					time_to_sleep;
    int					numb_of_times;
    unsigned long long	time_of_start;
    pthread_mutex_t		*forks;
    pthread_mutex_t		death;
    pthread_mutex_t		print;
}   t_data;


typedef struct s_philo
{
    pthread_t			t;
    pthread_t           dead;
    int					num;
	int					count_eat;
	unsigned long long	last_eat;
    pthread_mutex_t		left;
    pthread_mutex_t		right;
    pthread_mutex_t		mutex;
    t_data				*data;
}   t_philo;

int	ft_parser(t_data *data, char **argv);
int ft_init_mutex(t_data *data);
long long	ft_current_time(void);
int ft_init_philo(t_data *data, t_philo **philo);
int ft_init_pthread(t_data *data, t_philo *philo);
void	ft_printf_log(t_philo *philo, char *s);
void	*routine(void *void_philo);

#endif