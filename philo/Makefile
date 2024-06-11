NAME = philo
CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c init_utils.c write.c synchro_utils.c\
		 parse.c outils.c\
		 init.c  dinner.c\
		 getters_setters.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
