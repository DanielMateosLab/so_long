/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:57:35 by damateos          #+#    #+#             */
/*   Updated: 2024/07/26 20:05:56 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**is_valid_map(char **map)
{
	if (!map[0])
		return (ft_printf(EMPTY_MAP_ERR), NULL);
	return (map);
}
