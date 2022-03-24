NAME	=	philo_bonus

SRCS	=	ft_init_bonus.c ft_routine_bonus.c ft_parser_bonus.c philo_bonus.c ft_utils_bonus.c ft_strjoin.c

OBJS	= 	${SRCS:%.c=%.o}

HEADER	=	philo_bonus.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I.

.PHONY	:		all clean fclean re bonus

all		:	$(NAME)


%.o 	:		%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

