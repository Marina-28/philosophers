/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:42:38 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/20 16:22:50 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_unlock(t_philo *philo, int i)
{
	sem_post(philo->data->forks);
	if (i == 2)
		sem_post(philo->data->forks);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	long long	start_eat;

	sem_wait(philo->data->forks);
	if (philo->data->dead == 0)
		ft_printf_log(philo, "has taken a fork");
	else
		return (ft_unlock(philo, 1));
	sem_wait(philo->data->forks);
	if (philo->data->dead == 0)
		ft_printf_log(philo, "has taken a fork");
	else
		return (ft_unlock(philo, 2));
	start_eat = ft_current_time();
	philo->last_eat = start_eat;
	if (philo->data->dead == 0)
		ft_printf_log(philo, "is eating");
	else
		return (ft_unlock(philo, 2));
	while (ft_current_time() < (start_eat + philo->data->time_to_eat))
		usleep (100);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	long long	start_sleep;

	philo->count_eat = philo->count_eat + 1;
	if (philo->count_eat == philo->data->numb_of_times)
		sem_post(philo->stop);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	start_sleep = ft_current_time();
	if (philo->data->dead == 0)
		ft_printf_log(philo, "is sleeping");
	else
		return (1);
	while (ft_current_time() < (start_sleep + philo->data->time_to_sleep))
		usleep (100);
	if (philo->data->dead == 0)
		ft_printf_log(philo, "is thinking");
	else
		return (1);
	return (0);
}

void	*ft_check_dead(void *philo_v)
{
	t_philo		*philo;
	long long	time_without_eating;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->data->sem);
		time_without_eating = ft_current_time() - philo->last_eat;
		if (time_without_eating >= philo->data->time_to_die)
		{
			ft_printf_log(philo, "died");
			sem_wait(philo->data->print);
			philo->data->dead = 1;
			sem_post(philo->data->death);
			return (NULL);
		}
		sem_post(philo->data->sem);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *void_philo)
{
	t_philo		*philo;
	int			ret;
	pthread_t	t_dead;

	philo = (t_philo *)void_philo;
	ret = 0;
	if (pthread_create(&t_dead, NULL, &ft_check_dead, (void *)philo) != 0)
		return (NULL);
	pthread_detach(t_dead);
	while (ret == 0)
	{
		ret = ft_eat(philo);
		if (ret == 0)
			ret = ft_sleep(philo);
	}
	return (NULL);
}
