NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
SRCDIR = src
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCLUD = ./philo.h 
LIB = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)
	./philo 4 410 200 200

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME)

$(LIB):
	make bonus -C libft

clean:
	rm -rf $(OBJDIR)
	make clean -C libft/

	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

	@echo "Cleaning objects and executable"

re: fclean all

.PRECIOUS: $(OBJECTS)