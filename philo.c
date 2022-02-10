#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5)
		return (ft_error("Too few arguments\n"));
	else if (argc > 6)
		return (ft_error("Too many arguments\n"));
	if (ft_parser(&data, argv) == 1)
		return (ft_error("Invalid argument\n"));
	return (0);
}