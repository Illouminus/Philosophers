NAME = philo
CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building project $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleanup done."

re: fclean all

.PHONY: all clean fclean re
