/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:42:10 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/20 16:22:06 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_fill(char *s1, char *s2, char *str)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	while (n < (ft_strlen(s1) + ft_strlen(s2)))
	{
		while (s1[i] != '\0')
		{
			str[n] = s1[i];
			n++;
			i++;
		}
		if (s2[j] != '\0')
		{
			str[n] = s2[j];
			j++;
			n++;
		}
	}
	str[n] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_fill(s1, s2, str);
	return (str);
}

static int	ft_lennbr(int n, int i)
{
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		i++;
		n = n * (-1);
		i = ft_lennbr(n, i);
	}
	else if (n >= 10)
	{
		i++;
		i = ft_lennbr((n / 10), i);
	}
	else
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*nbr;

	i = ft_lennbr(n, 0);
	nbr = (char *)malloc((i + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	nbr[i] = '\0';
	if (n < 0)
	{
		nbr[0] = '-';
		if (n == -2147483648)
		{
			nbr[1] = '2';
			n = -147483648;
		}
		n = n * (-1);
	}
	while (n >= 10)
	{
		nbr[--i] = n % 10 + 48;
		n = n / 10;
	}
	nbr[--i] = n + 48;
	return (nbr);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)malloc((i + 1) * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
