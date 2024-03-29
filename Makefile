# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 14:39:52 by kamitsui          #+#    #+#              #
#    Updated: 2023/06/20 21:38:32 by kamitsui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
DEP_DIR = .dep
LIBFT_DIR = libft
PRINTF_DIR = ft_printf

# Source files
SRCS = \
	   pipex.c \
	   error.c \
	   initialize.c \
	   parent_process.c \
	   child_process.c \
	   set_input.c \
	   set_output.c \
	   exec_file.c \
	   substr_env.c

# Object files and dependency files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))

# name
NAME = pipex
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

# vpath for serching source files in multiple directories
vpath %.c $(SRC_DIR)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP -MF $(@:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)
INC = -I$(INC_DIR)

# Rules for building object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DEP_DIR)/%.d: %.c
	@mkdir -p $(DEP_DIR)

# Default target
all: $(NAME)

# Target
$(NAME): $(PRINTF) $(DEPS) $(OBJS)
	$(CC) $(PRINTF) $(OBJS) -o $(NAME)

# Library target
$(PRINTF): $(LIBFT)
	$(MAKE) -C $(PRINTF_DIR)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(NAME)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

# Clean and remove library target
fclean: clean
	rm -f $(NAME)

# Rebuild target
re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re
