/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:53 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 10:21:16 by damateos         ###   ########.fr       */
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
	str_array_loop_char(g->map, find_character, &g->char_pos);
	draw_tile(g->char_img, g->char_spritesheet,
		(t_point){.x = 0, .y = 0}, (t_point){.x = 0, .y = 0});
	if (mlx_image_to_window(g->mlx, g->char_img,
			TILE_SIZE * g->char_pos.x, TILE_SIZE * g->char_pos.y) == -1)
		return (ft_printf("Error drawing character"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	start_chart_movement(t_game *g, t_direction dir)
{
	t_point	new_pos;

	new_pos = (t_point){
		.x = g->char_pos.x - (dir == LEFT) + (dir == RIGHT),
		.y = g->char_pos.y - (dir == UP) + (dir == DOWN)};
	if (g->map[new_pos.y][new_pos.x] == MAP_WALL)
		return ;
	g->char_move.moving = 1;
	g->char_move.dir = dir;
	g->char_move.initial_time = mlx_get_time();
	g->char_move.target_pos.x = new_pos.x;
	g->char_move.target_pos.y = new_pos.y;
	draw_tile(g->char_img, g->char_spritesheet,
		(t_point){.x = dir, .y = 1}, (t_point){.x = 0, .y = 0});
}

void	finish_move(t_game *g)
{
	g->char_move.moving = 0;
	g->char_pos = g->char_move.target_pos;
	g->char_img->instances[0].x = TILE_SIZE * g->char_pos.x;
	g->char_img->instances[0].y = TILE_SIZE * g->char_pos.y;
	draw_tile(g->char_img, g->char_spritesheet,
		(t_point){.x = g->char_move.dir, .y = 0}, (t_point){.x = 0, .y = 0});
	ft_printf("Movements: %d\n", g->movements++);
}

void	move_char_hook(void *param)
{
	t_game		*g;
	double		speed;
	double		dtime;
	double		dpx;

	g = param;
	if (!g->char_move.moving)
		return ;
	dtime = mlx_get_time() - g->char_move.initial_time;
	if (dtime >= TILES_PER_SECOND)
		return (finish_move(g));
	speed = TILE_SIZE / TILES_PER_SECOND;
	dpx = dtime * speed;
	g->char_img->instances[0].x = TILE_SIZE * g->char_pos.x
		- (g->char_move.dir == LEFT) * dpx + (g->char_move.dir == RIGHT) * dpx;
	g->char_img->instances[0].y = TILE_SIZE * g->char_pos.y
		- (g->char_move.dir == UP) * dpx + (g->char_move.dir == DOWN) * dpx;
	if (g->char_move.frame != (int)(dpx / (TILE_SIZE / FRAMES_PER_TILE)))
	{
		g->char_move.frame = dpx / (TILE_SIZE / FRAMES_PER_TILE);
		draw_tile(g->char_img, g->char_spritesheet,
			(t_point){.x = g->char_move.dir, .y = g->char_move.frame},
			(t_point){.x = 0, .y = 0});
	}
}
