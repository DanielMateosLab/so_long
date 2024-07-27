/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:01 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 17:53:47 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	found_exit(char **map, t_point size, t_point pos)
// {

// }

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

	size.x = w;
	size.y = h;
	save_begin(map, &begin);
	return (1);
}
