/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:51:27 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/29 19:11:44 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_printf_log(t_philo *philo, char *s)
{
	long long	time;

	time = ft_current_time() - philo->data->time_of_start;
	sem_wait(philo->data->print);
	if (philo->data->dead == 0)
		printf("%lld %d %s\n", time, philo->num, s);
	sem_post(philo->data->print);
}

long long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_free_stop(t_philo *philo)
{
	int		i;
	char	*name;

	i = 0;
	while (philo[i].stop >= 0 && i < philo->data->nop)
	{
		sem_close(philo[i].stop);
		name = ft_name(i);
		if (name == NULL)
		{
			write(1, "Malloc fatal error\n", 19);
			exit (1);
		}
		sem_unlink(name);
		free(name);
		i++;
	}
}

void	ft_sem_unlink(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	sem_close(data->death);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->sem);
	sem_unlink("death");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("sem");
	ft_free_stop(philo);
}
