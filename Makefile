CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = so_long

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

BUILD_DIR = build

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/MLX42
MLX_BUILD_DIR = $(BUILD_DIR)/mlx
MLX42 = $(BUILD_DIR)/libmlx42.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42):
	cd $(MLX_DIR) && cmake -B ../$(MLX_BUILD_DIR) && make -C ../$(MLX_BUILD_DIR) -j4

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
# TODO: clean mlx

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

deb: CFLAGS += -g3 -fsanitize=address
deb: re

leaks: CFLAGS += -g3
leaks: re
