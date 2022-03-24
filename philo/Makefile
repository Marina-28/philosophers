NAME	=	philo

SRCS	=	ft_init.c ft_routine.c ft_parser.c philo.c ft_utils.c

OBJS	= 	${SRCS:%.c=%.o}

HEADER	=	philo.h

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

