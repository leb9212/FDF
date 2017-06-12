# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elee <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/27 21:33:26 by elee              #+#    #+#              #
#    Updated: 2017/06/11 18:01:30 by elee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LINKS = -framework OpenGL -framework AppKit

LIBFT = ./libft

MLX = minilibx_macos

SRCS = main.c read.c fdf.c transform.c array_ops.c draw.c

OBJS = $(SRCS:.c=.o)

INCS = includes/

all: $(NAME)

$(NAME):
	mkdir -p build/
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) -c $(addprefix srcs/, $(SRCS)) -I$(INCS) -I$(MLX)
	mv $(OBJS) build/
	$(CC) $(CFLAGS) $(LINKS) -o $(NAME) $(addprefix build/, $(OBJS)) \
		-I$(INCS) -I$(MLX) $(LIBFT)/libft.a $(MLX)/libmlx.a

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	/bin/rm -rf $(addprefix build/, $(OBJS))

fclean: clean
	make -C $(LIBFT) fclean
	make -C $(MLX) fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
