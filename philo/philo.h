/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:47:44 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/19 13:50:36 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int					nop;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					numb_of_times;
	int					dead;
	int					counter;
	long long			time_of_start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
	pthread_mutex_t		print;
}	t_data;

typedef struct s_philo
{
	pthread_t			t;
	int					num;
	int					count_eat;
	long long			last_eat;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_data				*data;
}	t_philo;

int			ft_parser(t_data *data, char **argv);
int			ft_init_mutex(t_data *data);
long long	ft_current_time(void);
void		ft_init_philo(t_data *data, t_philo **philo);
int			ft_init_pthread(t_data *data, t_philo *philo);
void		ft_printf_log(t_philo *philo, char *s);
void		*routine(void *void_philo);
void		ft_free_forks(t_data *data, int i);
void		ft_free(t_philo *philo, t_data *data);
int			init_philo_pthread(t_data *data, t_philo *philo);
void		*ft_check_eat(void *philo_v);
void		*ft_check_dead(void *philo_v);
int			ft_strlen(char *s);

#endif