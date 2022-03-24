/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:47:19 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/20 18:05:07 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *s, t_philo **philo)
{
	if (*philo != NULL)
		free(*philo);
	write(1, s, ft_strlen(s));
	return (1);
}

int	the_end(t_philo **philo, t_data *data, int j, int error)
{
	int	i;

	i = 0;
	while (i < j)
	{
		kill((*philo)[i].id, SIGKILL);
		waitpid(0, NULL, 0);
		i++;
	}
	ft_sem_unlink(data, *philo);
	free(*philo);
	if (error == 1)
		write(1, "Fork error\n", 11);
	while (1);
	return (error);
}

void	*ft_check_eat(void *philo_v)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	i = 0;
	while (i < philo->data->nop)
	{
		sem_wait(philo[i].stop);
		i++;
	}
	sem_wait(philo->data->print);
	printf("%lld All philosophers eat at least %d times!\n", \
	ft_current_time() \
	- philo->data->time_of_start, philo->data->numb_of_times);
	sem_post(philo->data->death);
	return (NULL);
}

static int	ft_start_process(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	t_eat;

	if (data->numb_of_times != -1)
	{
		if (pthread_create(&t_eat, NULL, &ft_check_eat, (void *)philo) != 0)
			return (1);
		pthread_detach(t_eat);
	}
	data->time_of_start = ft_current_time();
	i = -1;
	while (++i < data->nop)
	{
		philo[i].id = fork();
		if (philo[i].id < 0)
			return (i + 1);
		else if (philo[i].id == 0)
		{
			philo[i].last_eat = data->time_of_start;
			routine(&philo[i]);
			exit(0);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		j;

	philo = NULL;
	if (argc < 5)
		return (ft_error("Too few arguments\n", &philo));
	else if (argc > 6)
		return (ft_error("Too many arguments\n", &philo));
	if (ft_parser(&data, argv) == 1)
		return (ft_error("Invalid argument\n", &philo));
	philo = (t_philo *)malloc(sizeof(t_philo) * data.nop);
	if (philo == NULL)
		return (ft_error("Malloc error\n", &philo));
	if (ft_init_philo(&data, &philo) == 1)
		return (ft_error("Malloc error\n", &philo));
	if (ft_init_sem(&data) == 1)
	{
		ft_free_stop(philo);
		return (ft_error("Semaphore error\n", &philo));
	}
	j = ft_start_process(&data, philo);
	if (j != 0)
		return (the_end(&philo, &data, j, 1));
	sem_wait(data.death);
	return (the_end(&philo, &data, data.nop, 0));
}
