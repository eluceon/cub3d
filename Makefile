# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/26 14:41:26 by eluceon           #+#    #+#              #
#    Updated: 2021/02/12 15:05:20 by eluceon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


B&W = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
MLXDIR = minilibx_mms
MLXFLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lz
MLX_LIB	= libmlx.dylib
RM = rm -rf

NAME = cub3D

OBJDIR = ./obj/
OBJDIR_BONUS = ./obj/bonus/
HEADERDIR = ./includes/

SRCDIR = ./
SRCS = cub3d.c
OBJ = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
HEADER = $(addprefix $(HEADERDIR), cub3d.h)

SRC_ENGINE_DIR = ./engine/
SRCS_ENGINE = loop_control.c draw_map2d.c move_player.c rotate_player.c \
			draw.c draw_window.c key_control.c draw_wall.c sprite_utils.c \
			draw_sprites.c speed.c draw_weapon_bonus.c draw_floor.c \
			jump_player.c draw_hud.c save_bitmap.c exit_game.c
OBJ_ENGINE = $(addprefix $(OBJDIR), $(SRCS_ENGINE:.c=.o))
HEADER_ENGINE = $(addprefix $(HEADERDIR), engine.h)

SRCS_ENGINE_BONUS = loop_control.c draw_map2d.c move_player.c rotate_player.c \
			draw.c draw_window.c key_control.c draw_wall.c sprite_utils.c \
			draw_sprites.c speed.c draw_floor.c draw_weapon_bonus.c \
			jump_player.c draw_hud.c save_bitmap.c exit_game.c
OBJ_ENGINE_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_ENGINE_BONUS:.c=.o))

SRC_PARSER_DIR = ./parser/
SRCS_PARSER = parser.c parse_params.c parse_map.c check_map.c
OBJ_PARSER = $(addprefix $(OBJDIR), $(SRCS_PARSER:.c=.o))
HEADER_PARSER = $(addprefix $(HEADERDIR), parser.h)

SRCS_PARSER_BONUS = parser_bonus.c parse_params.c parse_map.c check_map.c
OBJ_PARSER_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_PARSER_BONUS:.c=.o))

SRC_UTILS_DIR = ./utils/
SRCS_UTILS = ft_lstnew.c ft_calloc.c ft_lstadd_back.c\
			ft_putendl_fd.c ft_strcmp.c ft_check_extension.c ft_skip_spaces.c \
			ft_atoi_cub.c ft_lst_clear.c ft_lstsize.c ft_iswhitespace.c \
			ft_strlen.c	ft_isemtyline.c
OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
OBJ_UTILSB_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_UTILS:.c=.o))
HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

SRC_GNL_DIR = ./gnl/
SRCS_GNL = get_next_line.c get_next_line_utils.c
OBJ_GNL = $(addprefix $(OBJDIR), $(SRCS_GNL:.c=.o))
OBJ_GNL_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_GNL:.c=.o))
HEADER_GNL = $(addprefix $(HEADERDIR), get_next_line.h)

OBJ_ALL = $(OBJ) $(OBJ_ENGINE) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_GNL)

OBJ_BONUS_ALL = $(OBJ) $(OBJ_ENGINE_BONUS) $(OBJ_UTILS) \
				 $(OBJ_GNL) $(OBJ_PARSER_BONUS)

all: $(NAME)

$(NAME): $(MLXDIR) $(OBJDIR) $(OBJ_ALL)
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)/$(MLX_LIB) .
	$(CC) $(CFLAGS) $(OBJ_ALL) -o $@ $(MLXFLAGS)
	@echo "$(PURPLE) $(NAME) has been created $(B&W)"

bonus: $(OBJDIR) $(OBJDIR_BONUS) $(OBJ_BONUS_ALL)
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)/$(MLX_LIB) .
	$(CC) $(CFLAGS) $(OBJ_BONUS_ALL) -o $(NAME) $(MLXFLAGS)
	@echo "$(PURPLE) $(NAME) has been created $(B&W)"	

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_BONUS):
	mkdir -p $(OBJDIR_BONUS)

#############################
##    START compilation    ##
#############################

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)has been created $(B&W)"

##############################
##    ENGINE compilation    ##
##############################

$(OBJ_ENGINE): $(OBJDIR)%.o: $(SRC_ENGINE_DIR)%.c $(HEADER_ENGINE)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for engine has been created $(B&W)"

####################################
##    ENGINE BONUS compilation    ##
####################################

$(OBJ_ENGINE_BONUS): $(OBJDIR_BONUS)%.o: $(SRC_ENGINE_DIR)%.c $(HEADER_ENGINE)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for engine has been created $(B&W)"

##############################
##    PARSER compilation    ##
##############################

$(OBJ_PARSER): $(OBJDIR)%.o: $(SRC_PARSER_DIR)%.c $(HEADER_PARSER)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for parser has been created $(B&W)"

####################################
##    PARSER BONUS compilation    ##
####################################

$(OBJ_PARSER_BONUS): $(OBJDIR_BONUS)%.o: $(SRC_PARSER_DIR)%.c $(HEADER_PARSER)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for parser has been created $(B&W)"

#############################
##    UTILS compilation    ##
#############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for utils has been created $(B&W)"

###########################
##    GNL compilation    ##
###########################

$(OBJ_GNL): $(OBJDIR)%.o: $(SRC_GNL_DIR)%.c $(HEADER_GNL)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for gnl has been created $(B&W)"

clean:
	$(MAKE)	clean -C $(MLXDIR)
	$(RM) $(OBJDIR)
	@echo "$(RED) $(MLXDIR) has been deleted"
	@echo "$(RED) $(OBJDIR) has been deleted $(B&W)"

fclean: clean
	$(RM) $(NAME) $(MLX_LIB)
	$(RM) "cub3D.bmp"
	@echo "$(RED) $(NAME) has been deleted $(B&W)"
	@echo "$(RED) cub3D.bmp has been deleted"

re:	fclean all

.PHONY: all bonus clean fclean re
