/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:51:27 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/13 17:56:18 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_forks(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j != i)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
	free(data->forks);
}

void	ft_printf_log(t_philo *philo, char *s)
{
	long long	time;

	time = ft_current_time() - philo->data->time_of_start;
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->dead == 0)
		printf("%lld %d %s\n", time, philo->num, s);
	pthread_mutex_unlock(&philo->data->print);
}

long long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_free(t_philo *philo, t_data *data)
{
	ft_free_forks(data, data->nop);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	free(philo);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
