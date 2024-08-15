/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:44:18 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:17 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialize_draw_floor_data(t_draw_floor_data *d, t_game *g)
{
	mlx_texture_t	*texture;

	ft_bzero(d, sizeof(t_draw_floor_data));
	texture = mlx_load_png("textures/elements.png");
	if (!texture)
		return (ft_printf("Error loading floor texture"), 1);
	g->elements_img = mlx_texture_to_image(g->mlx, texture);
	if (!g->elements_img)
		return (ft_printf("Error creating floor tiles image"), 1);
	mlx_delete_texture(texture);
	d->floor_img = mlx_new_image(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE);
	if (!d->floor_img)
		return (ft_printf("Error creating floor image"), 1);
	d->walls_img = mlx_new_image(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE);
	if (!d->walls_img)
		return (ft_printf("Error creating walls image"), 1);
	if (BASE_TILE_SIZE != TILE_SIZE)
		mlx_resize_image(
			g->elements_img,
			g->elements_img->width * TILE_SIZE / BASE_TILE_SIZE,
			g->elements_img->height * TILE_SIZE / BASE_TILE_SIZE);
	return (0);
}

void	draw_wall(t_game *g, t_draw_floor_data d)
{
	if (d.y == 0 || d.y == g->height - 1
		|| d.x == 0 || d.x == g->width - 1)
		draw_tile(d.walls_img, g->elements_img,
			(t_point){.x = 11, .y = 0},
			(t_point){.x = d.x, .y = d.y});
	else
		draw_tile(d.walls_img, g->elements_img,
			(t_point){.x = 12, .y = 0},
			(t_point){.x = d.x, .y = d.y});
}

int	draw_floor(t_game *g)
{
	t_draw_floor_data	d;

	if (initialize_draw_floor_data(&d, g) == 1)
		return (EXIT_FAILURE);
	while (g->map[d.y])
	{
		d.x = 0;
		while (g->map[d.y][d.x])
		{
			draw_tile(d.floor_img, g->elements_img,
				(t_point){.x = pseudo_random(d.x, d.y) % 7, .y = 0},
				(t_point){.x = d.x, .y = d.y});
			if (g->map[d.y][d.x] == MAP_WALL)
				draw_wall(g, d);
			d.x++;
		}
		d.y++;
	}
	if (
		mlx_image_to_window(g->mlx, d.floor_img, 0, 0) == -1
		|| mlx_image_to_window(g->mlx, d.walls_img, 0, 0) == -1
	)
		return (ft_printf("Error drawing floor"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
