/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:54:44 by damateos          #+#    #+#             */
/*   Updated: 2024/08/16 14:32:40 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_action_keys_hook(void *param)
{
	t_game	*game;
	mlx_t	*mlx;

	game = param;
	mlx = game->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (game->player_move.moving)
		return ;
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		start_player_movement(game, UP);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		start_player_movement(game, DOWN);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
		start_player_movement(game, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
		start_player_movement(game, RIGHT);
}

int	is_valid_extension(char *file_name)
{
	return (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".ber", 4) == 0);
}

void	set_map_metadata(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->width = ft_strlen(game->map[0]);
	game->height = str_array_len(game->map);
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == MAP_COLLECTABLE)
				game->tot_coll++;
			j++;
		}
		i++;
	}
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init(game->width * TILE_SIZE,
			game->height * TILE_SIZE, "so_long", false);
	if (!game->mlx)
		return (ft_printf(INIT_GAME_ERR, 1));
	if (draw_floor(game) == EXIT_FAILURE
		|| draw_collectables(game) == EXIT_FAILURE
		|| draw_flag(game) == EXIT_FAILURE
		|| draw_player(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_loop_hook(game->mlx, animate_collectables_and_flag_hook, game);
	mlx_loop_hook(game->mlx, ft_action_keys_hook, game);
	mlx_loop_hook(game->mlx, move_player_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}

// TODO: use mlx42 from campus source, remove test folder and
// GIMP source before submitting
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf(ARGC_ERR), 1);
	if (!is_valid_extension(argv[1]))
		return (ft_printf(FILE_EXT_ERR), 1);
	game.map = read_map(argv[1]);
	if (!game.map)
		return (1);
	if (!is_valid_map(game.map))
		return (str_array_clear(game.map), 1);
	set_map_metadata(&game);
	if (init_game(&game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	str_array_clear(game.map);
}
