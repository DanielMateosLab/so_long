/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:17:12 by damateos          #+#    #+#             */
/*   Updated: 2024/08/12 17:55:01 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	draw_collectables(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	g->collectables_img = mlx_new_image(g->mlx, TILE_SIZE, TILE_SIZE);
	if (!g->collectables_img)
		return (EXIT_FAILURE);
	draw_tile(g->collectables_img, g->elements_img,
		(t_point){.x = COLL_TILE_START, .y = 0}, (t_point){.x = 0, .y = 0});
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == MAP_COLLECTABLE)
				mlx_image_to_window(g->mlx, g->collectables_img,
					TILE_SIZE * x, TILE_SIZE * y);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
