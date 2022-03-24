/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:47:44 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/20 16:15:34 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_data
{
	int			nop;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			numb_of_times;
	int			dead;
	long long	time_of_start;
	sem_t		*forks;
	sem_t		*death;
	sem_t		*print;
	sem_t		*sem;
}	t_data;

typedef struct s_philo
{
	pid_t		id;
	int			num;
	int			count_eat;
	long long	last_eat;
	sem_t		*stop;
	t_data		*data;
}	t_philo;

int			ft_parser(t_data *data, char **argv);
int			ft_init_sem(t_data *data);
long long	ft_current_time(void);
int			ft_init_philo(t_data *data, t_philo **philo);
void		ft_printf_log(t_philo *philo, char *s);
void		*routine(void *void_philo);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
char		*ft_name(int i);
void		ft_free_stop(t_philo *philo);
void		ft_sem_unlink(t_data *data, t_philo *philo);
#endif