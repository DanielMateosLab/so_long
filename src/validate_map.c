/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:57:35 by damateos          #+#    #+#             */
/*   Updated: 2024/07/26 20:19:31 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	return (map);
}
