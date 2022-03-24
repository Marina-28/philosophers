/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:42:38 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/19 14:46:08 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_unlock(t_philo *philo, int i)
{
	if (i == 1)
		pthread_mutex_unlock(philo->left);
	else if (i == 2)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else if (i == 3)
	{
		pthread_mutex_unlock(philo->left);
		return (2);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	long long	start_eat;

	pthread_mutex_lock(philo->left);
	if (philo->data->dead == 0)
		ft_printf_log(philo, "has taken a fork");
	else
		return (ft_unlock(philo, 1));
	if (philo->right == NULL)
		return (ft_unlock(philo, 3));
	pthread_mutex_lock(philo->right);
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
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->data->numb_of_times != -1 && \
		philo->count_eat == philo->data->numb_of_times)
		philo->data->counter = philo->data->counter + 1;
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

void	*routine(void *void_philo)
{
	t_philo		*philo;
	int			ret;

	philo = (t_philo *)void_philo;
	while (1)
	{
		ret = ft_eat(philo);
		if (ret == 0)
			ret = ft_sleep(philo);
		if (ret != 0)
		{
			if (ret == 2)
			{
				while (ft_current_time()
					< (philo->last_eat + philo->data->time_to_die))
					usleep (100);
			}
			return (NULL);
		}
	}
	return (NULL);
}
