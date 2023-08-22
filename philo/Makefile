NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread
SRCDIR = ./
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCLUD = ./philo.h 

.PHONY: all clean fclean re

all: $(NAME)

run: all
	./philo 4 410 200 200

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)

	@echo "Cleaning objects and executable"

re: fclean all

.PRECIOUS: $(OBJECTS)
