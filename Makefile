# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 21:42:49 by abbaraka          #+#    #+#              #
#    Updated: 2024/09/24 16:34:38 by abbaraka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= cub3D

SRCS= main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS= $(SRCS:.c=.o)

HEADER= cub3D.h

CC = cc

MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit \
			 MLX42/build/libmlx42.a -Iinclude -ldl -lglfw 

CFLAGS= -Wall -Wextra -Werror -O3 -ffast-math

RM= rm -rf

$(NAME): $(OBJS)

		$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) 

%.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@ 

all : $(NAME)

clean : 
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
