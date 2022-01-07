# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toni <toni@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 03:16:14 by toni              #+#    #+#              #
#    Updated: 2022/01/07 18:31:33 by toni             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = $(BUILD_PATH)philo

# COMPILER / FLAGS
CC = gcc
CFLAGS := -Wall -Werror -Wextra -I ./inc/ -O1

# ADD PTHREAD LIB ONLY ON LINUX TO COMPILATION FLAGS
ifeq ($(shell uname -s),Linux)
	CFLAGS += -pthread
endif

# PATHS
SRC_PATH = ./src/
BUILD_PATH = ./build/
OBJ_PATH = $(BUILD_PATH)obj/

# FILES
SRC := main.c parse_input.c init_philos.c thread_worker.c philo_actions.c philo_routine.c \
		utils/str_utils.c utils/prnt_utils.c utils/time_utils.c utils/getter_setter.c
SRC := $(addprefix $(SRC_PATH), $(SRC))

OBJ := $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# COMPILATION RULES
all: $(BIN)
	@cp $(BIN) $(notdir $(BIN))

$(BIN): $(OBJ)
	@echo $(Y)Compiling [$(BIN)]...$(X)
	@$(CC) $(CFLAGS) $(OBJ) -o $(BIN)
	@echo $(G)Finished [$(BIN)]$(X)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $^ -o $@
	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
	@printf $(UP)$(CUT)

re: fclean all

# CLEANING RULES
clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
		$(RM) -rf $(OBJ_PATH); \
		echo $(R)Cleaning" "[$(OBJ_PATH)]...$(X); \
	fi;

fclean: clean
	@if [ -f "$(BIN)" ]; then \
		$(RM) -f $(BIN); \
		echo $(R)Cleaning" "[$(BIN)]...$(X); \
	fi;
	@if [ -d "$(BUILD_PATH)" ]; then \
		$(RM) -rf $(BUILD_PATH); \
		echo $(R)Cleaning" "[$(BUILD_PATH)]...$(X); \
	fi;
	@if [ -f "$(notdir $(BIN))" ]; then \
		$(RM) -f $(notdir $(BIN)); \
		echo $(R)Cleaning" "[./$(notdir $(BIN))]...$(X); \
	fi;

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

.PHONY: all re clean fclean