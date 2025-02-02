# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/28 20:00:46 by ymeziane          #+#    #+#              #
#    Updated: 2023/12/07 18:47:18 by ymeziane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
NC=\033[0m

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror

INCLUDES = -I./inc -I./libft/inc

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRC_DIR = src
BONUS_SRC_DIR = src_bonus
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

SRC_FILES = pipex check_input error children get_path free
BONUS_SRC_FILES = pipex_bonus check_input_bonus error_bonus here_doc_bonus init_pipes_bonus children_bonus get_path_bonus free_bonus

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR)/, $(addsuffix .c, $(BONUS_SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR)/, $(addsuffix .o, $(BONUS_SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "${GREEN}Creating executable $(NAME)${NC}"
	@$(CC) $(OBJ) $(LIBFT) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "${YELLOW}Compiling $<${NC}"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "${YELLOW}Compiling $< (Bonus)${NC}"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "${GREEN}Building libft${NC}"
	@$(MAKE) -s -C $(LIBFT_DIR)

bonus: $(BONUS_OBJ) $(LIBFT)
	@echo "${GREEN}Creating bonus executable $(NAME)${NC}"
	@$(CC) $(BONUS_OBJ) $(LIBFT) -o $(NAME)

clean:
	@echo "${RED}Cleaning object files${NC}"
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "${YELLOW}Cleaning libft${NC}"
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "${RED}Removing executable $(NAME)${NC}"
	@rm -f $(NAME)
	@echo "${YELLOW}Full clean for libft${NC}"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
