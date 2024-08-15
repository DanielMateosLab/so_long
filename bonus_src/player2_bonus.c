/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:26:19 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:49:27 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	pick_collectable(t_game *g)
{
	size_t			i;
	mlx_instance_t	*coll_instances;

	g->map[g->player_pos.y][g->player_pos.x] = MAP_FLOOR;
	g->curr_coll++;
	draw_collectables_counter(g);
	i = 0;
	coll_instances = g->collectables_img->instances;
	while (i < g->collectables_img->count)
	{
		if (coll_instances[i].x == g->player_pos.x * TILE_SIZE
			&& coll_instances[i].y == g->player_pos.y * TILE_SIZE)
			coll_instances[i].enabled = 0;
		i++;
	}
}

void	finish_move(t_game *g)
{
	g->player_move.moving = 0;
	g->player_pos = g->player_move.target_pos;
	g->player_img->instances[0].x = TILE_SIZE * g->player_pos.x;
	g->player_img->instances[0].y = TILE_SIZE * g->player_pos.y;
	if (g->map[g->player_pos.y][g->player_pos.x] == MAP_COLLECTABLE)
		pick_collectable(g);
	if (g->map[g->player_pos.y][g->player_pos.x] == MAP_EXIT
		&& g->curr_coll == g->tot_coll)
		return (ft_printf("Mission accomplished! You took %d moves\n",
				g->movements), mlx_close_window(g->mlx));
	draw_tile(g->player_img, g->player_spritesheet,
		(t_point){.x = g->player_move.dir, .y = 0}, (t_point){.x = 0, .y = 0});
	ft_printf("Movements: %d\n", g->movements++);
}
