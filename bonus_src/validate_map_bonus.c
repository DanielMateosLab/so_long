/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:57:35 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:10:41 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	has_valid_tile_counts(char **map)
{
	t_validate_map_data	d;

	ft_bzero(&d, sizeof(t_validate_map_data));
	while (map[d.i])
	{
		d.j = 0;
		while (map[d.i][d.j])
		{
			if (map[d.i][d.j] == MAP_EXIT)
				d.exits++;
			else if (map[d.i][d.j] == MAP_COLLECTABLE)
				d.collectables++;
			else if (map[d.i][d.j] == MAP_INITIAL_POS)
				d.initial_pos++;
			d.j++;
		}
		d.i++;
	}
	if (d.exits != 1 || d.collectables < 1 || d.initial_pos != 1)
		return (
			ft_printf(INVALID_TILES_COUNT_ERR),
			ft_printf("\texit: %d, obj: %d, init: %d\n",
				d.exits, d.collectables, d.initial_pos),
			0);
	return (1);
}

int	is_surrounded_by_walls(char **map, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (i == 0 || i == h - 1)
		{
			j = 0;
			while (j < w)
			{
				if (map[i][j] != MAP_WALL)
					return (0);
				j++;
			}
		}
		else
		{
			if (map[i][0] != MAP_WALL || map[i][w - 1] != MAP_WALL)
				return (0);
		}
		i++;
	}
	return (1);
}

char	has_forbidden_components(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_char_any_of(map[i][j],
				5,
				MAP_FLOOR,
				MAP_WALL,
				MAP_COLLECTABLE,
				MAP_EXIT,
				MAP_INITIAL_POS))
				return (map[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_rectangle_map(char **map, int *w, int *h)
{
	size_t	len;
	int		i;

	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (0);
		i++;
	}
	*w = len;
	*h = i;
	return (1);
}

char	**is_valid_map(char **map)
{
	int	w;
	int	h;

	if (!map[0])
		return (ft_printf(EMPTY_MAP_ERR), NULL);
	if (!is_rectangle_map(map, &w, &h))
		return (ft_printf(RECT_MAP_ERR), NULL);
	if (has_forbidden_components(map))
		return (ft_printf(COMPONENTS_ERR), NULL);
	if (!is_surrounded_by_walls(map, w, h))
		return (ft_printf(WALL_ERR), NULL);
	if (!has_valid_tile_counts(map))
		return (NULL);
	if (!has_exit(map, w, h))
		return (ft_printf(PATH_ERR), NULL);
	return (map);
}
