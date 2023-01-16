#-----------------------------------------------#
#-----------------[ SRCS NAME ]-----------------#
#-----------------------------------------------#

SRCS		=	main.c ft_parse.c ft_init.c ft_start.c ft_philo.c ft_watch_philo.c ft_destroy.c ft_utils.c

#-----------------------------------------------#
#----------------[ COMPILATION ]----------------#
#-----------------------------------------------#

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g

HEADERS			=	philosophers.h

NAME			=	philo

OBJS			=	$(SRCS:.c=.o)	

#-----------------------------------------------#
#-------------------[ TARGET ]------------------#
#-----------------------------------------------#

all:			$(NAME)

%.o:			%.c $(HEADERS)
				$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			all clean

.PHONY:			all clean fclean re