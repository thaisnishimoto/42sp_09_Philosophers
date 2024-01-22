# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:39:03 by tmina-ni          #+#    #+#              #
#    Updated: 2024/01/22 15:58:16 by tmina-ni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================FLAGS=========================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MAKE_NO_PRINT = $(MAKE) --no-print-directory

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
	$(MAKE_NO_PRINT) clean -C $(LIB_PATH)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE_NO_PRINT) fclean -C $(LIB_PATH)

re: fclean all

.PHONY: all leak gdb clean fclean re
