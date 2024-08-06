/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:43:49 by damateos          #+#    #+#             */
/*   Updated: 2024/08/06 22:01:43 by damateos         ###   ########.fr       */
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
# define TILE_SIZE 32

typedef struct s_game
{
	mlx_t	*mlx;
	char	**map;
	int		width;
	int		height;
	int		curr_coll;
	int		tot_coll;
	int		movements;
}	t_game;

typedef struct s_validate_map_data
{
	int	i;
	int	j;
	int	exits;
	int	collectables;
	int	initial_pos;
}	t_validate_map_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_draw_floor_data
{
	mlx_texture_t	*texture;
	mlx_image_t		*tiles_img;
	mlx_image_t		*floor_img;
	int				y;
	int				x;
}	t_draw_floor_data;

char	**read_map(const char *path);
char	**is_valid_map(char **map);
void	save_begin(char **map, t_point *begin);
int		has_exit(char **map, int w, int h);

// TODO: move to libft
void	*str_array_clear(char **table);
char	**str_array_copy(char **map);
char	**str_array_resize(char **arr, size_t len, size_t new_len);
size_t	str_array_len(char **arr);
int		draw_floor(t_game *g);

#endif
