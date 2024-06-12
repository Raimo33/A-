# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 15:33:59 by craimond          #+#    #+#              #
#    Updated: 2024/06/12 23:31:13 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs
HDRS_DIR = srcs/headers
OBJS_DIR = build

SRCS = $(shell find $(SRCS_DIR) -name '*.cpp')
HDRS = $(shell find $(HDRS_DIR) -name '*.hpp' -o -name '*.h' -o -name '*.tpp')
OBJS = $(patsubst $(SRCS_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))

LEAK_REPORT = leaks.log

CC = g++
VERSION = 2a
CFLAGS = -Wall -Wextra -Werror -std=c++$(VERSION) -I${SFML_INCS_DIR}
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

RM = rm -rf

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: ${NAME}

${NAME}: $(OBJS)
	@$(CC) $(CFLAGS) -o ${NAME} $(OBJS) -L${SFML_LIBS_DIR} -lsfml-graphics -lsfml-window -lsfml-system -lpthread
	@echo "$(GREEN)compiled ${NAME}$(NC)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)removed object files$(NC)"

fclean: clean
	@$(RM) ${NAME}
	@echo "$(RED)removed ${NAME}$(NC)"
	@$(RM) $(LEAK_REPORT)
	@echo "$(RED)removed $(LEAK_REPORT)$(NC)"

leaks: all
	@valgrind $(VALGRIND_FLAGS) ./${NAME} 2> $(LEAK_REPORT)
	@echo "$(GREEN)leak report generated$(NC)"

re: fclean all

.PHONY: all clean re

.SILENT: all ${NAME} $(OBJS) clean fclean re

.IGNORE: clean fclean