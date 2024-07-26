/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:57:35 by damateos          #+#    #+#             */
/*   Updated: 2024/07/26 20:28:19 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// TODO: move to libft
#include <stdarg.h>

int	ft_char_any_of(char target, int num_args, ...)
{
	va_list	args;
	char	current;
	int		i;

	va_start(args, num_args);
	i = 0;
	while (i < num_args)
	{
		current = va_arg(args, int);
		if (target == current)
		{
			va_end(args);
			return (1);
		}
		i++;
	}
	va_end(args);
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
	return (map);
}
