# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 09:22:45 by mjallada          #+#    #+#              #
#    Updated: 2022/11/02 13:49:28 by mjallada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME				:= cub3D

CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror -I$(INC) -I.. -g

INC_DIR				:= include
SRC_DIR				:= src
BIN_DIR				:= bin

INC					:= /usr/include
INCLIB				:= $(INC)/../lib
LFLAGS				:= -L./minilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm

LIB_DIR				:= libft
LIB					:= $(shell echo $(LIB_DIR) | cut -c 4-)

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
BGREEN				:= \033[1;92m
RED					:= \033[0;31m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
PURPLE				:= \033[0;35m
IPURPLE				:= \033[3;35m
RED_BLINK			:= \033[31;5m
GREEN_BLINK			:= \033[92;5m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES		:=	main\
					map_check_borders\
					map_check_colors\
					map_check_file\
					map_check_textures\
					map_parsing\
					map_parsing_utils\
					map_parsing_utils2\
					map_structure\
					mlx_move_setup\
					mlx_render_utils\
					mlx_setup\
					raycasting\
					raycasting_utils\
					raycasting_init\
					render_drawing\
					render_minimap\
					render_wall_projection\
					utils\
					utils_free
OBJ_FILES		:=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# **************************************************************************** #
# RULES

all: header $(NAME)

bonus: all

$(NAME): minilib $(OBJ_FILES)
	@make --no-print-directory -C libft
	@$(CC) -g -o $(NAME) $(OBJ_FILES) $(LFLAGS) -L $(LIB_DIR) -l $(LIB)
	@echo "\n🧟 $(GREEN_BLINK)$(NAME) compiled$(END_COLOR) 🔫\n"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	@$(CC) -MD -g -c $(CFLAGS) -I $(INC_DIR) -I $(LIB_DIR)/$(INC_DIR) -I./minilibx-linux $< -o $@
	@printf "\r> $(BLUE)compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@echo "$(IPURPLE)Created $(BIN_DIR)/ directory.$(END_COLOR)"

minilib:
	@echo "\ncompiling minilibX...\n"
	@make --no-print-directory -s -C minilibx-linux
	@echo "\n$(GREEN)minilibX compiled$(END_COLOR)\n"

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) all object & dependency files cleaned.$(END_COLOR)"
	@make clean --no-print-directory -C libft
	@make clean --no-print-directory -s -C minilibx-linux

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) executable file cleaned.$(END_COLOR)"
	@rm -f libft/libft.a
	@echo "$(YELLOW)$(LIB_DIR) executable file cleaned as well!$(END_COLOR)"

re: fclean space all

header:
	@echo "🕋 $(NAME)\n"

space:
	@echo

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re header space bonus minilib
