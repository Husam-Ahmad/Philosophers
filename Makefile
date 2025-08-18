NAME = philo

SRCS = philo.c\
		action.c\
		init.c\
		thread.c\
		state.c\

OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror# -fsanitize=thread -g

all: $(NAME) 

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)
		rm -f *fier

re: fclean all

.PHONY: all clean fclean re