/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:44:18 by damateos          #+#    #+#             */
/*   Updated: 2024/08/16 14:25:21 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	initialize_draw_floor_data(t_game *g)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("textures/elements.png");
	if (!texture)
		return (ft_printf("Error loading floor texture"), 1);
	g->elements_img = mlx_texture_to_image(g->mlx, texture);
	if (!g->elements_img)
		return (ft_printf("Error creating floor tiles image"), 1);
	mlx_delete_texture(texture);
	g->floor_img = mlx_new_image(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE);
	if (!g->floor_img)
		return (ft_printf("Error creating floor image"), 1);
	g->walls_img = mlx_new_image(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE);
	if (!g->walls_img)
		return (ft_printf("Error creating walls image"), 1);
	if (BASE_TILE_SIZE != TILE_SIZE)
		mlx_resize_image(
			g->elements_img,
			g->elements_img->width * TILE_SIZE / BASE_TILE_SIZE,
			g->elements_img->height * TILE_SIZE / BASE_TILE_SIZE);
	return (0);
}

void	draw_wall(t_game *g, t_point p)
{
	if (p.y == 0 || p.y == g->height - 1
		|| p.x == 0 || p.x == g->width - 1)
		draw_tile(g->walls_img, g->elements_img,
			(t_point){.x = 11, .y = 0},
			(t_point){.x = p.x, .y = p.y});
	else
		draw_tile(g->walls_img, g->elements_img,
			(t_point){.x = 12, .y = 0},
			(t_point){.x = p.x, .y = p.y});
}

void	draw_floor_elements(char **arr, t_point pos, int *stop, void *param)
{
	t_game	*g;

	g = param;
	(void)stop;
	(void)arr;
	draw_tile(g->floor_img, g->elements_img,
		(t_point){.x = pseudo_random(pos.x, pos.y) % 7, .y = 0},
		(t_point){.x = pos.x, .y = pos.y});
	if (g->map[pos.y][pos.x] == MAP_WALL)
		draw_wall(g, pos);
	if (g->map[pos.y][pos.x] == MAP_ENEMY_PATROL)
		draw_tile(g->walls_img, g->elements_img,
			(t_point){.x = ENEMY_TILE_START, .y = 0},
			(t_point){.x = pos.x, .y = pos.y});
}

int	draw_floor(t_game *g)
{
	if (initialize_draw_floor_data(g) == 1)
		return (EXIT_FAILURE);
	str_array_loop_char(g->map, draw_floor_elements, g);
	if (
		mlx_image_to_window(g->mlx, g->floor_img, 0, 0) == -1
		|| mlx_image_to_window(g->mlx, g->walls_img, 0, 0) == -1
	)
		return (ft_printf("Error drawing floor"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
