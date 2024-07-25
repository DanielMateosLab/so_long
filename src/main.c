/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:54:44 by damateos          #+#    #+#             */
/*   Updated: 2024/07/25 21:05:21 by damateos         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf(ARGC_ERR), 1);
	if (!is_valid_extension(argv[1]))
		return (ft_printf(FILE_EXT_ERR), 1);
	game.map = read_map(argv[1]);
	if (!game.map)
		return (EXIT_FAILURE);
	// TODO: continue
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0)))
	{
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game.mlx, 128, 128)))
	{
		mlx_close_window(game.mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_loop_hook(game.mlx, ft_action_keys_hook, game.mlx);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

