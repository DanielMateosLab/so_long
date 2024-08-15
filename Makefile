CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibs/libft/include \
	-Ilibs/MLX42/include/MLX42

# TODO: add dependency on tile size
ifdef TILE_SIZE
	CFLAGS += -DTILE_SIZE=$(TILE_SIZE)
endif

NAME = so_long
BONUS_NAME = so_long_bonus
BUILD_DIR = build

SRCS = src/main.c src/read_map.c src/validate_map.c src/has_exit.c \
	src/ft_str_arr.c src/floor.c src/draw_utils.c \
	src/collectables_and_flag.c	src/player.c src/player2.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
HEADER = include/so_long.h

BONUS_SRCS = bonus_src/main_bonus.c bonus_src/read_map_bonus.c \
	bonus_src/validate_map_bonus.c bonus_src/has_exit_bonus.c \
	bonus_src/ft_str_arr_bonus.c bonus_src/floor_bonus.c \
	bonus_src/draw_utils_bonus.c bonus_src/collectables_and_flag_bonus.c \
	bonus_src/player_bonus.c bonus_src/player2_bonus.c \
	bonus_src/counter_bonus.c
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BUILD_DIR)/%.o)
BONUS_HEADER = include/so_long_bonus.h

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX42 = $(MLX_BUILD_DIR)/libmlx42.a

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft \
		-L$(MLX_BUILD_DIR) -lmlx42 -lglfw

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS) -L$(LIBFT_DIR) -lft \
		-L$(MLX_BUILD_DIR) -lmlx42 -lglfw

$(OBJS): $(HEADER)

$(BONUS_OBJS): $(BONUS_HEADER)

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
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus

deb: CFLAGS += -g3 -fsanitize=address
deb: re

leaks: CFLAGS += -g3
leaks: re

bonus_leaks: CFLAGS += -g3
bonus_leaks: bonus
	leaks --atExit -q -- ./$(BONUS_NAME) maps/map3.ber

run_leaks_mac: leaks
	leaks --atExit -q -- ./$(NAME) maps/map3.ber
