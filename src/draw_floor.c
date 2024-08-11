/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:44:18 by damateos          #+#    #+#             */
/*   Updated: 2024/08/11 22:03:12 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(mlx_image_t *dest, mlx_image_t *src,
		t_point src_p, t_point dst_p)
{
	t_point	dp;
	int		i;

	dp.y = 0;
	while (dp.y < BASE_TILE_SIZE)
	{
		dp.x = 0;
		while (dp.x < BASE_TILE_SIZE)
		{
			i = get_pixel_i(src_p, dp, src->width);
			mlx_put_pixel(dest, dst_p.x * BASE_TILE_SIZE + dp.x,
				dst_p.y * BASE_TILE_SIZE + dp.y,
				src->pixels[i] << 24 | src->pixels[i + 1] << 16
				| src->pixels[i + 2] << 8 | src->pixels[i + 3]);
			dp.x++;
		}
		dp.y++;
	}
}

int	initialize_draw_floor_data(t_draw_floor_data *data, t_game *g)
{
	mlx_texture_t	*texture;

	ft_bzero(data, sizeof(t_draw_floor_data));
	texture = mlx_load_png("src/textures/elements.png");
	if (!texture)
		return (ft_printf("Error loading floor texture"), 1);
	g->elements_img = mlx_texture_to_image(g->mlx, texture);
	if (!g->elements_img)
		return (ft_printf("Error creating floor tiles image"), 1);
	mlx_delete_texture(texture);
	data->floor_img = mlx_new_image(g->mlx, g->width * BASE_TILE_SIZE,
			g->height * BASE_TILE_SIZE);
	if (!data->floor_img)
		return (ft_printf("Error creating floor image"), 1);
	data->walls_img = mlx_new_image(g->mlx, g->width * BASE_TILE_SIZE,
			g->height * BASE_TILE_SIZE);
	if (!data->walls_img)
		return (ft_printf("Error creating walls image"), 1);
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

int	resize_and_put_imgs(t_game *g, t_draw_floor_data *d)
{
	if (BASE_TILE_SIZE != TILE_SIZE)
	{
		mlx_resize_image(d->floor_img,
			g->width * TILE_SIZE, g->height * TILE_SIZE);
		mlx_resize_image(d->walls_img,
			g->width * TILE_SIZE, g->height * TILE_SIZE);
	}
	if (
		mlx_image_to_window(g->mlx, d->floor_img, 0, 0) == -1
		|| mlx_image_to_window(g->mlx, d->walls_img, 0, 0) == -1
	)
		return (ft_printf("Error drawing floor"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	if (resize_and_put_imgs(g, &d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
