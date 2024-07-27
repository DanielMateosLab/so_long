/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:43:49 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 15:16:16 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>

# include "../libs/libft/include/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define ARGC_ERR "Error\nInvalid args. Usage: ./so_long FILE_PATH\n"
# define FILE_EXT_ERR "Error\nInvalid map extension. Allowed: .ber\n"
# define EMPTY_MAP_ERR "Error\nEmpty map.\n"
# define RECT_MAP_ERR "Error\nMap is not a rectangle.\n"
# define COMPONENTS_ERR "Error\nForbidden component. Allowed: 0, 1, C, E, P\n"
# define WALL_ERR "Error\nThe map is not surrounded by walls\n"
# define MIN_COMPS_ERR "Error\nMap should countain one exit,\
 at least one object and the initial position\n"
# define PATH_ERR "Error\nThere is not a valid path\n"
# define READ_MAP_ERR "Error\nError reading the map.\n"

char	**read_map(const char *path);
void	*ft_clear_str_arr(char **table);
char	**is_valid_map(char **map);

typedef struct s_game
{
	mlx_t				*mlx;
	char				**map;
}						t_game;

#endif
