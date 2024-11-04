# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:39:22 by abadouab          #+#    #+#              #
#    Updated: 2024/11/03 18:58:13 by abbaraka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

NAME_B		=	cub3D_bonus

SRCS		=	Core/Cub3D.c \
				Core/Objects.c \
				Parser/Parser.c \
				Parser/ParseMap.c \
				Parser/ParseColor.c \
				Parser/ParseTexture.c \
				RayCast/RayCast.c \
				RayCast/RayCalc.c \
				RayCast/RayHit.c \
				Player/Movements.c \
				Core/Render.c \
				Minimap/Minimap.c \
				Minimap/mapFrame.c \
				Graphics/LoadTextures.c \
				Graphics/ApplyTextures.c \
				Error/ErrorHandler.c

SRCS_B		=	Bonus/Core/Cub3D.c \
				Bonus/Core/Objects.c \
				Bonus/Parser/Parser.c \
				Bonus/Parser/ParseMap.c \
				Bonus/Parser/ParseColor.c \
				Bonus/Parser/ParseTexture.c \
				Bonus/RayCast/RayCast.c \
				Bonus/RayCast/RayCalc.c \
				Bonus/RayCast/RayHit.c \
				Bonus/Player/Movements.c \
				Bonus/Core/Render.c \
				Bonus/Doors/Doors.c \
				Bonus/Doors/Door_functions.c \
				Bonus/Minimap/Minimap.c \
				Bonus/Minimap/mapFrame.c \
				Bonus/Graphics/LoadTextures.c \
				Bonus/Graphics/ApplyTextures.c \
				Bonus/Error/ErrorHandler.c

OBJS_DIR	=	.Objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_B		=	$(addprefix $(OBJS_DIR), $(SRCS_B:.c=.o))

MLX			=	MLX42/MLX
MLX42		=	MLX42
HEADER		=	Includes/Cub3D.h Includes/Types_Cub3D.h

HEADER_B	=	Includes/Cub3D_bonus.h Includes/Types_bonus.h

CLIB		=	CLib
ARLIB		=	CLib/libar.a

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror # -g -fsanitize=address
RM			=	rm -fr

SHORT		=	-L$(CLIB) -lar -L $(MLX) -l mlx42 -lglfw
INCLUDES	=	-I $(CLIB) -I Includes -I $(MLX42)/include/MLX42/

GREEN		=	"\033[1;32m"
YELOW		=	"\033[1;33m"
REDCL		=	"\033[1;31m"
RESET		=	"\033[0m"

all: $(MLX42) start $(CLIB) $(NAME) finish

bonus: $(MLX42) start $(CLIB) $(NAME_B) finish

start:
	@printf "\n"
	@echo $(GREEN)"Starting build..."
	@sleep 1
	@printf "Loading [ "

finish:
	@echo $(GREEN) ] 100%$(RESET)
	@echo $(GREEN)Project built.$(RESET)
	@printf "\n"

removing:
	@if [ -d $(MLX) ]; then rm -rf $(MLX); fi

$(CLIB):
	@make -sC $(CLIB) --no-print-directory

$(MLX42):
	@git submodule update --init
	@cmake -B $(MLX) -S $(MLX42)
	@make -C $(MLX) --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ $(SHORT) -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: %.c $(HEADER) $(ARLIB)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@printf $(GREEN)"."$(RESET)

$(NAME_B): $(OBJS_B)
	@$(CC) $(FLAGS) $^ $(SHORT) -o $(NAME_B)

$(OBJS_B): $(OBJS_DIR)%.o: %.c $(HEADER_B) $(ARLIB)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@printf $(GREEN)"."$(RESET)

clean:
	@$(RM) $(OBJS_DIR)
	@make clean -C $(CLIB) --no-print-directory
	@echo $(YELOW)Cleaning up 🧹💫$(RESET)

fclean: removing clean
	@$(RM) $(NAME) $(NAME_B)
	@make fclean -C $(CLIB) --no-print-directory
	@echo $(REDCL)Purging all files 🗑️$(RESET)

re: fclean all

.PHONY: $(CLIB) $(MLX42)
