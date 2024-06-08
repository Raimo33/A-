# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 15:33:59 by craimond          #+#    #+#              #
#    Updated: 2024/06/07 21:19:12 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = aStar

SRCS_DIR = srcs
HDRS_DIR = srcs/headers
SFML_DIR = /usr/lib/x86_64-linux-gnu

SRCS = $(addprefix $(SRCS_DIR)/, main.cpp)
HDRS = $(addprefix $(HDRS_DIR)/, constants.hpp)
OBJS = $(SRCS:.cpp=.o)

LEAK_REPORT = leaks.log

CC = g++
VERSION = 2a
CFLAGS = -Wall -Wextra -Werror -std=c++$(VERSION) -I$(SFML_DIR)/include
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

RM = rm -rf

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lpthread
	@echo "$(GREEN)compiled $(NAME)$(NC)"

%.o: %.cpp $(HDRS)
	@mkdir -p $(dir $@)
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)removed object files$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)removed $(NAME)$(NC)"
	@$(RM) $(LEAK_REPORT)
	@echo "$(RED)removed $(LEAK_REPORT)$(NC)"

leaks: all
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) 2> $(LEAK_REPORT)
	@echo "$(GREEN)leak report generated$(NC)"

re: fclean all

.PHONY: all clean re

.SILENT: all $(NAME) $(OBJS) clean fclean re

.IGNORE: clean fclean