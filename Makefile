# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 23:25:13 by gorg              #+#    #+#              #
#    Updated: 2025/01/11 13:42:57 by gorg             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2

###
LIBFT_DIR = ./Extras/libft
GNL_DIR = ./Extras/gnl
MLX_DIR = ./Extras/mlx
SRCS_DIR = ./srcs/

###
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a
GNL_SRC = $(GNL_DIR)/get_next_line.c
GNL_OBJ = $(GNL_SRC:.c=.o)
FILES = fdf_main.c fdf_init.c fdf_parsing_utils.c fdf_parsing.c fdf_render.c fdf_render_utils.c

###
SRCS = $(addprefix $(SRCS_DIR),$(FILES)) $(GNL_SRC)
OBJS = $(SRCS:.c=.o)

###
all: libmlx $(LIBFT) $(MLX) $(NAME)

libmlx:
	@if [ ! -d "Extras/mlx/.git" ]; then \
		echo "MLX42 not found, cloning..."; \
		git clone https://github.com/42Paris/minilibx-linux.git Extras/mlx; \
	else \
		echo "MLX42 clone ok."; \
	fi

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) -lm -L $(MLX_DIR) -lX11 -lXext

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

Extras/gnl/get_next_line.o: Extras/gnl/get_next_line.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re make libmlx
