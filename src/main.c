/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:54:44 by damateos          #+#    #+#             */
/*   Updated: 2024/08/02 20:07:27 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// TODO: remove stdio
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t *image;

void	ft_action_keys_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
		image->instances[0].x += 5;
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
	game->mlx = mlx_init(game->width * TILE_SIZE, game->height * TILE_SIZE, "so_long", false);
	if (!game->mlx)
		return (ft_printf(INIT_GAME_ERR, 1));
	mlx_loop_hook(game->mlx, ft_action_keys_hook, game->mlx);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}

int main(int argc, char **argv)
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
	return (init_game(&game));
	// if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0)))
	// {
	// 	ft_printf("%s", mlx_strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }
	// if (!(image = mlx_new_image(game.mlx, 128, 128)))
	// {
	// 	mlx_close_window(game.mlx);
	// 	ft_printf("%s", mlx_strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(game.mlx, image, 0, 0) == -1)
	// {
	// 	mlx_close_window(game.mlx);
	// 	ft_printf("%s", mlx_strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }

	// mlx_loop_hook(game.mlx, ft_action_keys_hook, game.mlx);

	// mlx_loop(game.mlx);
	// mlx_terminate(game.mlx);
}

