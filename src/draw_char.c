/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:53 by damateos          #+#    #+#             */
/*   Updated: 2024/08/14 18:46:17 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_character(char **arr, t_point pos, int *stop, void *param)
{
	t_point	*tile;

	tile = param;
	tile->x = -1;
	tile->y = -1;
	if (arr[pos.y][pos.x] == MAP_INITIAL_POS)
	{
		tile->x = pos.x;
		tile->y = pos.y;
		*stop = 1;
	}
}

int	draw_char(t_game *g)
{
	t_point			initial_pos;
	mlx_texture_t	*texture;

	texture = mlx_load_png("src/textures/char.png");
	if (!texture)
		return (ft_printf("Error loading character texture"), EXIT_FAILURE);
	g->char_spritesheet = mlx_texture_to_image(g->mlx, texture);
	mlx_delete_texture(texture);
	if (!g->char_spritesheet)
		return (ft_printf("Error creating char spritesheet img"), EXIT_FAILURE);
	g->char_img = mlx_new_image(g->mlx, TILE_SIZE, TILE_SIZE);
	if (!g->char_img)
		return (ft_printf("Error creating character image"), EXIT_FAILURE);
	if (BASE_TILE_SIZE != TILE_SIZE)
		mlx_resize_image(
			g->char_spritesheet,
			g->char_spritesheet->width * TILE_SIZE / BASE_TILE_SIZE,
			g->char_spritesheet->height * TILE_SIZE / BASE_TILE_SIZE);
	str_array_loop_char(g->map, find_character, &initial_pos);
	draw_tile(g->char_img, g->char_spritesheet,
		(t_point){.x = 0, .y = 0}, (t_point){.x = 0, .y = 0});
	mlx_image_to_window(g->mlx, g->char_img,
		TILE_SIZE * initial_pos.x, TILE_SIZE * initial_pos.y);
	return (EXIT_SUCCESS);
}
