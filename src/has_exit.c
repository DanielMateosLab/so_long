/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:01 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 18:37:50 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	found_exit(char **map, t_point *size, int x, int y)
{
	char	tile;

	if (x >= size->x || y >= size->y)
		return (0);
	tile = map[y][x];
	if (tile == MAP_EXIT)
		return (1);
	if (tile == MAP_WALL || tile == MAP_FLOOD)
		return (0);
	map[y][x] = MAP_FLOOD;
	return (
		found_exit(map, size, x + 1, y)
		|| found_exit(map, size, x - 1, y)
		|| found_exit(map, size, x, y + 1)
		|| found_exit(map, size, x, y - 1)
	);
}

void	save_begin(char **map, t_point *begin)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == MAP_INITIAL_POS)
			{
				begin->x = j;
				begin->y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

int	has_exit(char **map, int w, int h)
{
	t_point	size;
	t_point	begin;
	char	**map_cpy;

	size.x = w;
	size.y = h;
	map_cpy = str_array_copy(map);
	save_begin(map_cpy, &begin);
	if (
		!found_exit(map_cpy, &size, begin.x - 1, begin.y)
		|| !found_exit(map_cpy, &size, begin.x + 1, begin.y)
		|| !found_exit(map_cpy, &size, begin.x, begin.y - 1)
		|| !found_exit(map_cpy, &size, begin.x, begin.y + 1)
	)
		return (0);
	str_array_clear(map_cpy);
	return (1);
}
