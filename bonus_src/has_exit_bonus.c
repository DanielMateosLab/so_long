/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:01 by damateos          #+#    #+#             */
/*   Updated: 2024/07/28 00:01:57 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	are_exit_and_collectables_filled(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == MAP_COLLECTABLE || map[i][j] == MAP_EXIT)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	flood_fill(char **map, t_point *size, int x, int y)
{
	char	tile;

	if (x >= size->x || y >= size->y)
		return ;
	tile = map[y][x];
	if (tile == MAP_WALL || tile == MAP_FLOOD)
		return ;
	map[y][x] = MAP_FLOOD;
	flood_fill(map, size, x + 1, y);
	flood_fill(map, size, x - 1, y);
	flood_fill(map, size, x, y + 1);
	flood_fill(map, size, x, y - 1);
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
	int		result;

	size.x = w;
	size.y = h;
	map_cpy = str_array_copy(map);
	save_begin(map_cpy, &begin);
	flood_fill(map_cpy, &size, begin.x, begin.y);
	result = are_exit_and_collectables_filled(map_cpy);
	str_array_clear(map_cpy);
	return (result);
}
