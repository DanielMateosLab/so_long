/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:43:49 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:47:29 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# define ARGC_ERR "Error\nInvalid args. Usage: ./so_long FILE_PATH\n"
# define FILE_EXT_ERR "Error\nInvalid map extension. Allowed: .ber\n"
# define EMPTY_MAP_ERR "Error\nEmpty map.\n"
# define RECT_MAP_ERR "Error\nMap is not a rectangle.\n"
# define COMPONENTS_ERR "Error\nForbidden component. Allowed: 0, 1, C, E, P\n"
# define WALL_ERR "Error\nThe map is not surrounded by walls\n"
# define INVALID_TILES_COUNT_ERR "Error\nMap should countain one exit,\
 at least one object and the initial position\n"
# define FILE_PATH_ERR "Error\nNo file in the given path.\n"
# define PATH_ERR "Error\nThe map can not be solved!\n"
# define READ_MAP_ERR "Error\nError reading the map.\n"
# define INIT_GAME_ERR "Error\nCouldn't initialize mlx.\n"
# define MAP_EXIT 'E'
# define MAP_INITIAL_POS 'P'
# define MAP_COLLECTABLE 'C'
# define MAP_WALL '1'
# define MAP_FLOOR '0'
# define MAP_FLOOD 'F'
# define BASE_TILE_SIZE 16
# ifndef TILE_SIZE
#  define TILE_SIZE 24
# endif
# define COLL_TILE_START 7
# define WALL_TILE_START 11
# define EXIT_TILE_START 13
# define ELEMENTS_COUNT 17
# define FRAMES_PER_TILE 4
# define TILES_PER_SECOND 0.25

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef enum e_direction
{
	DOWN,
	UP,
	LEFT,
	RIGHT
}	t_direction;

typedef struct s_char_move
{
	int			moving;
	double		initial_time;
	// When time ends, we move the character to the target position
	t_point		target_pos;
	t_direction	dir;
	int			frame;
}	t_char_move;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	int				width;
	int				height;
	int				curr_coll;
	int				tot_coll;
	int				movements;
	mlx_image_t		*elements_img;
	mlx_image_t		*collectables_img;
	mlx_image_t		*flag_img;
	mlx_image_t		*player_spritesheet;
	mlx_image_t		*player_img;
	mlx_image_t		*colls_count_img;
	mlx_image_t		*count_overlay_img;
	t_point			exit;
	t_char_move		player_move;
	t_point			player_pos;
}	t_game;

typedef struct s_validate_map_data
{
	int	i;
	int	j;
	int	exits;
	int	collectables;
	int	initial_pos;
}	t_validate_map_data;

typedef struct s_draw_floor_data
{
	mlx_image_t		*floor_img;
	mlx_image_t		*walls_img;
	int				y;
	int				x;
}	t_draw_floor_data;

// TODO: move to libft
void	*str_array_clear(char **table);
char	**str_array_copy(char **map);
char	**str_array_resize(char **arr, size_t len, size_t new_len);
size_t	str_array_len(char **arr);
// END TODO

char	**read_map(const char *path);
char	**is_valid_map(char **map);
void	save_begin(char **map, t_point *begin);
int		has_exit(char **map, int w, int h);
int		draw_floor(t_game *g);
int		get_pixel_i(t_point point, t_point delta, int width);
int		pseudo_random(int x, int y);
void	draw_tile(mlx_image_t *dest, mlx_image_t *src,
			t_point src_p, t_point dst_p);
int		draw_collectables(t_game *g);
void	animate_collectables_and_flag_hook(void *param);
int		draw_flag(t_game *g);
void	str_array_loop_char(char **arr,
			void (*fn)(char **arr, t_point pos, int *stop, void *),
			void *param);
int		draw_player(t_game *g);
void	start_player_movement(t_game *g, t_direction dir);
void	move_player_hook(void *param);
void	finish_move(t_game *g);
int		draw_collectables_counter(t_game *game);

#endif
