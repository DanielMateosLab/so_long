CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
# ifeq ($(shell uname -s),Darwin)
#     CFLAGS += -framework Cocoa -framework OpenGL -framework IOKit
# endif

NAME = so_long
BUILD_DIR = build

SRCS = src/main.c src/read_map.c src/validate_map.c src/has_exit.c src/ft_str_arr.c \
		src/draw_floor.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
HEADER = include/so_long.h

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX42 = $(MLX_BUILD_DIR)/libmlx42.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx42 -lglfw

$(OBJS): $(HEADER)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) -j4

$(MLX42):
	cd $(MLX_DIR) && cmake -B build && make -C build -j4

clean:
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_BUILD_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

deb: CFLAGS += -g3 -fsanitize=address
deb: re

leaks: CFLAGS += -g3
leaks: re
