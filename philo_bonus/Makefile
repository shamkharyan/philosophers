NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra
CC = cc
# DEBUG = -fsanitize=thread

SRC_PATH = ./srcs
INC_PATH = ./includes

SRCS = \
		$(SRC_PATH)/utils.c \
		$(SRC_PATH)/philo.c \
		$(SRC_PATH)/initialization.c \
		$(SRC_PATH)/monitor.c \
		$(SRC_PATH)/life.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $(NAME)


%.o: %.c Makefile
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
