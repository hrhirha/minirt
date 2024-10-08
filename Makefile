# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrhirha <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/23 09:54:42 by hrhirha           #+#    #+#              #
#    Updated: 2020/10/14 14:00:18 by hrhirha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
LIBFT = libft/libft.a
LIBMLX = libmlx.dylib
MAKE_LIBFT = make -C libft/ && make bonus -C libft/
MAKE_MLX = make -C minilibx_mms_20200219/
CC = clang -Wall -Wextra -Werror
MLX = $(LIBMLX) -framework OpenGL -framework AppKit
UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
MLX = $(LIBMLX) -lm -lX11 -lXext
endif
SRCS =	main.c \
		file_parsing/*.c \
		gnl/get_next_line.c \
		rendering/*.c \
		intersections/*.c \
		utils/*.c \
		errors/*.c \
		keys.c \
		bmp.c
		
OBJS = *.o

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE_LIBFT)
	$(MAKE_MLX)
	mv minilibx_mms_20200219/libmlx.dylib ./$(LIBMLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(OBJS) : $(SRCS)
	$(CC) -c $(SRCS)

clean :
	make clean -C libft/
	make clean -C minilibx_mms_20200219/
	rm -rf *.o

fclean : clean
	make fclean -C libft/
	rm -rf $(NAME)
	rm -rf libmlx.dylib

re : fclean $(NAME)
