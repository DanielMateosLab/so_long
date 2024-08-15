/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_and_flag_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:17:12 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:10:32 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	draw_collectables(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	g->collectables_img = mlx_new_image(g->mlx, TILE_SIZE, TILE_SIZE);
	if (!g->collectables_img)
		return (ft_printf("Error creating collectables image"), EXIT_FAILURE);
	draw_tile(g->collectables_img, g->elements_img,
		(t_point){.x = COLL_TILE_START, .y = 0}, (t_point){.x = 0, .y = 0});
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == MAP_COLLECTABLE)
			{
				if (mlx_image_to_window(g->mlx, g->collectables_img,
						TILE_SIZE * x, TILE_SIZE * y) == -1)
					return (ft_printf("Error drawing collectables"), 1);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

void	find_exit(char **arr, t_point pos, int *stop, void *param)
{
	t_point	*tile;

	tile = param;
	tile->x = -1;
	tile->y = -1;
	if (arr[pos.y][pos.x] == MAP_EXIT)
	{
		tile->x = pos.x;
		tile->y = pos.y;
		*stop = 1;
	}
}

int	draw_flag(t_game *g)
{
	g->flag_img = mlx_new_image(g->mlx, TILE_SIZE, TILE_SIZE);
	if (!g->flag_img)
		return (ft_printf("Error creating flag image"), 1);
	str_array_loop_char(g->map, find_exit, &g->exit);
	draw_tile(g->flag_img, g->elements_img,
		(t_point){.x = EXIT_TILE_START, .y = 0}, (t_point){.x = 0, .y = 0});
	if (mlx_image_to_window(g->mlx, g->flag_img, g->exit.x * TILE_SIZE,
			g->exit.y * TILE_SIZE) == -1)
		return (ft_printf("Error drawing flag"), 1);
	return (0);
}

void	animate_collectables_and_flag_hook(void *param)
{
	t_game			*g;
	static double	last_update = 0;
	static int		i = 1;

	g = param;
	if (mlx_get_time() - last_update > 0.1)
	{
		draw_tile(g->collectables_img, g->elements_img,
			(t_point){.x = COLL_TILE_START + i, .y = 0},
			(t_point){.x = 0, .y = 0});
		draw_tile(g->flag_img, g->elements_img,
			(t_point){.x = EXIT_TILE_START + i, .y = 0},
			(t_point){.x = 0, .y = 0});
		if (i == 3)
			i = 0;
		else
			i++;
		last_update = mlx_get_time();
	}
}
