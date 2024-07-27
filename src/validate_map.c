/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:57:35 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 15:26:11 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	is_rectangle_map(char **map)
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
	return (1);
}

char	**is_valid_map(char **map)
{
	if (!map[0])
		return (ft_printf(EMPTY_MAP_ERR), NULL);
	if (!is_rectangle_map(map))
		return (ft_printf(RECT_MAP_ERR), NULL);
	if (has_forbidden_components(map))
		return (ft_printf(COMPONENTS_ERR), NULL);
	return (map);
}
