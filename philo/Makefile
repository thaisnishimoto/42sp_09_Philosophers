# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:39:03 by tmina-ni          #+#    #+#              #
#    Updated: 2024/04/29 17:01:15 by tmina-ni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================FLAGS=========================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RACE_FLAGS = -o2 -fsanitize=thread -pthread
MAKE_NO_PRINT = $(MAKE) --no-print-directory
# -fsanitize=thread
#================================PATHS=========================================#

HEADER_PATH = ./include
SRC_PATH = ./src

#================================FILES=========================================#

NAME = philo
SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(SRC:.c=.o)
HEADER = $(HEADER_PATH)/philo.h

#================================RULES=========================================#

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAG)

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

race:
	$(CC) $(CFLAGS) $(RACE_FLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAG)

#================================LEAKS=========================================#

leak:
	@echo "ARG1=number_of_philosophers"
	@echo "ARG2=time_to_die"
	@echo "ARG3=time_to_eat"
	@echo "ARG4=time_to_sleep"
	@echo "[ARG5=number_of_times_each_philosopher_must_eat]"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)
	
#================================LEAKS=========================================#

gdb:
	@echo "ARG1=number_of_philosophers"
	@echo "ARG2=time_to_die"
	@echo "ARG3=time_to_eat"
	@echo "ARG4=time_to_sleep"
	@echo "[ARG5=number_of_times_each_philosopher_must_eat]"
	gdb --tui --args ./$(NAME) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)

#================================CLEAN=========================================#

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all leak gdb clean fclean re
