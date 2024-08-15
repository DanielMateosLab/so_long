/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:54:44 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:46:51 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	draw_collectables_counter(t_game *game)
{
	char	*count_str;
	char	*formatted_msg;

	if (game->count_overlay_img)
		mlx_delete_image(game->mlx, game->count_overlay_img);
	if (game->colls_count_img)
		mlx_delete_image(game->mlx, game->colls_count_img);
	count_str = ft_itoa(game->curr_coll);
	if (!count_str)
		return (ft_printf("Error creating collectables count string"),
			EXIT_FAILURE);
	formatted_msg = ft_strjoin("Collectables: ", count_str);
	free(count_str);
	if (!formatted_msg)
		return (ft_printf("Error creating collectables count message"),
			EXIT_FAILURE);
	game->colls_count_img = mlx_put_string(game->mlx, formatted_msg, 0, 0);
	free(formatted_msg);
	if (!game->colls_count_img)
		return (ft_printf("Error drawing collectables count"),
			EXIT_FAILURE);
	game->count_overlay_img = mlx_new_image(game->mlx,
			game->colls_count_img->width, game->colls_count_img->height);
	ft_memset(game->count_overlay_img->pixels, 100,
		game->count_overlay_img->width * game->count_overlay_img->height * sizeof(int32_t));
	if (mlx_image_to_window(game->mlx, game->count_overlay_img, 0, 0) == -1)
		return (ft_printf("Error drawing collectables count overlay"),
			EXIT_FAILURE);
	game->count_overlay_img->instances[0].z -= 2;
	return (EXIT_SUCCESS);
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
		|| draw_player(game) == EXIT_FAILURE
		|| draw_collectables_counter(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_loop_hook(game->mlx, animate_collectables_and_flag_hook, game);
	mlx_loop_hook(game->mlx, ft_action_keys_hook, game);
	mlx_loop_hook(game->mlx, move_player_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}

// TODO: use mlx42 from campus source, remove test folder before submitting
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
