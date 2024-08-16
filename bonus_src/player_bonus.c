/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:53 by damateos          #+#    #+#             */
/*   Updated: 2024/08/16 13:59:05 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	find_player(char **arr, t_point pos, int *stop, void *param)
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

int	draw_player(t_game *g)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("textures/player.png");
	if (!texture)
		return (ft_printf("Error loading player texture"), EXIT_FAILURE);
	g->player_spritesheet = mlx_texture_to_image(g->mlx, texture);
	mlx_delete_texture(texture);
	if (!g->player_spritesheet)
		return (ft_printf("Error creating char spritesheet img"), EXIT_FAILURE);
	g->player_img = mlx_new_image(g->mlx, TILE_SIZE, TILE_SIZE);
	if (!g->player_img)
		return (ft_printf("Error creating player image"), EXIT_FAILURE);
	if (BASE_TILE_SIZE != TILE_SIZE)
		mlx_resize_image(
			g->player_spritesheet,
			g->player_spritesheet->width * TILE_SIZE / BASE_TILE_SIZE,
			g->player_spritesheet->height * TILE_SIZE / BASE_TILE_SIZE);
	str_array_loop_char(g->map, find_player, &g->player_pos);
	draw_tile(g->player_img, g->player_spritesheet,
		(t_point){.x = 0, .y = 0}, (t_point){.x = 0, .y = 0});
	if (mlx_image_to_window(g->mlx, g->player_img,
			TILE_SIZE * g->player_pos.x, TILE_SIZE * g->player_pos.y) == -1)
		return (ft_printf("Error drawing player"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	start_player_movement(t_game *g, t_direction dir)
{
	t_point	new_pos;

	new_pos = (t_point){
		.x = g->player_pos.x - (dir == LEFT) + (dir == RIGHT),
		.y = g->player_pos.y - (dir == UP) + (dir == DOWN)};
	if (g->map[new_pos.y][new_pos.x] == MAP_WALL)
		return ;
	if (g->map[new_pos.y][new_pos.x] == MAP_ENEMY_PATROL)
		g->player_move.enemy_target = 1;
	g->player_move.moving = 1;
	g->player_move.dir = dir;
	g->player_move.initial_time = mlx_get_time();
	g->player_move.target_pos.x = new_pos.x;
	g->player_move.target_pos.y = new_pos.y;
	draw_tile(g->player_img, g->player_spritesheet,
		(t_point){.x = dir, .y = 1}, (t_point){.x = 0, .y = 0});
}

void	animate_player(t_game *g, double dpx)
{
	int	new_frame;

	new_frame = dpx / (TILE_SIZE / FRAMES_PER_TILE);
	if (g->player_move.frame != new_frame)
	{
		g->player_move.frame = new_frame;
		draw_tile(g->player_img, g->player_spritesheet,
			(t_point){.x = g->player_move.dir, .y = g->player_move.frame},
			(t_point){.x = 0, .y = 0});
	}
}

void	move_player_hook(void *param)
{
	t_game		*g;
	double		speed;
	double		dtime;
	double		dpx;

	g = param;
	if (!g->player_move.moving)
		return ;
	dtime = mlx_get_time() - g->player_move.initial_time;
	if (dtime >= TILES_PER_SECOND)
		return (finish_move(g));
	if (dtime >= 0.25 * TILES_PER_SECOND && g->player_move.enemy_target)
		return (ft_printf("Game over! Touched enemy patrol.\n"),
			mlx_close_window(g->mlx));
	speed = TILE_SIZE / TILES_PER_SECOND;
	dpx = dtime * speed;
	g->player_img->instances[0].x = TILE_SIZE * g->player_pos.x
		- (g->player_move.dir == LEFT) * dpx
		+ (g->player_move.dir == RIGHT) * dpx;
	g->player_img->instances[0].y = TILE_SIZE * g->player_pos.y
		- (g->player_move.dir == UP) * dpx + (g->player_move.dir == DOWN) * dpx;
	animate_player(g, dpx);
}
