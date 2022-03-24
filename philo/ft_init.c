/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:55:02 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/19 14:46:08 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		i++;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			ft_free_forks(data, i);
			return (1);
		}
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		ft_free_forks(data, i);
		return (1);
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		pthread_mutex_destroy(&data->death);
		ft_free_forks(data, i);
		return (1);
	}
	pthread_mutex_lock(&data->death);
	return (0);
}

void	ft_init_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		(*philo)[i].num = i + 1;
		(*philo)[i].count_eat = 0;
		(*philo)[i].last_eat = 0;
		(*philo)[i].data = data;
		(*philo)[i].left = &data->forks[i];
		(*philo)[i].right = NULL;
		if (data->nop != 1)
		{
			if ((i + 1) == data->nop)
				(*philo)[i].right = &data->forks[0];
			else
				(*philo)[i].right = &data->forks[i + 1];
		}
		i++;
	}
}

void	*ft_check_dead(void *philo_v)
{
	t_philo		*philo;
	long long	time_without_eating;
	int			i;

	philo = (t_philo *)philo_v;
	while (philo[0].last_eat == 0)
		usleep(100);
	while (philo->data->dead == 0)
	{
		i = 0;
		while (i < philo->data->nop)
		{
			time_without_eating = ft_current_time() - philo[i].last_eat;
			if (time_without_eating >= philo->data->time_to_die)
			{
				ft_printf_log(&philo[i], "died");
				philo->data->dead = 1;
				pthread_mutex_unlock(&philo->data->death);
				return (NULL);
			}
			usleep(1000);
		}
	}
	return (NULL);
}

void	*ft_check_eat(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (philo->data->dead == 0)
	{
		if (philo->data->counter == philo->data->nop)
		{
			philo->data->dead = 1;
			printf("%lld All philosophers eat at least %d times!\n", \
			ft_current_time() \
			- philo->data->time_of_start, philo->data->numb_of_times);
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	init_philo_pthread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		philo[i].last_eat = data->time_of_start;
		if (pthread_create(&philo[i].t, NULL, routine, &philo[i]) != 0)
			return (1);
		i = i + 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->nop)
	{
		philo[i].last_eat = data->time_of_start;
		if (pthread_create(&philo[i].t, NULL, routine, &philo[i]) != 0)
			return (1);
		i = i + 2;
	}
	return (0);
}
