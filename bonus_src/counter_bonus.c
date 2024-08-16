/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:55:38 by damateos          #+#    #+#             */
/*   Updated: 2024/08/16 13:31:13 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*generate_count_msg(t_game *game)
{
	char	*count_str;
	char	*formatted_msg;

	count_str = ft_itoa(game->movements);
	if (!count_str)
		return (NULL);
	formatted_msg = ft_strjoin("Movements: ", count_str);
	free(count_str);
	if (!formatted_msg)
		return (NULL);
	return (formatted_msg);
}

int	put_overlay_img(t_game *game)
{
	size_t		i;
	mlx_image_t	*img;

	game->count_overlay_img = mlx_new_image(game->mlx,
			game->colls_count_img->width, game->colls_count_img->height);
	if (!game->count_overlay_img)
		return (ft_printf("Error creating count overlay img"), EXIT_FAILURE);
	img = game->count_overlay_img;
	i = 0;
	while (i < img->width * img->height * sizeof(int32_t))
	{
		img->pixels[i] = 0;
		i++;
	}
	i = 3;
	while (i < img->width * img->height * sizeof(int32_t))
	{
		img->pixels[i] = 100;
		i += 4;
	}
	if (mlx_image_to_window(game->mlx, img, 0, 0) == -1)
		return (ft_printf("Error drawing count overlay"),
			EXIT_FAILURE);
	img->instances[0].z = game->colls_count_img->instances[0].z - 1;
	return (EXIT_SUCCESS);
}

int	draw_counter(t_game *game)
{
	char	*formatted_msg;

	if (game->count_overlay_img)
		mlx_delete_image(game->mlx, game->count_overlay_img);
	if (game->colls_count_img)
		mlx_delete_image(game->mlx, game->colls_count_img);
	formatted_msg = generate_count_msg(game);
	if (!formatted_msg)
		return (ft_printf("Error creating count message"), EXIT_FAILURE);
	game->colls_count_img = mlx_put_string(game->mlx, formatted_msg, 0, 0);
	free(formatted_msg);
	if (!game->colls_count_img)
		return (ft_printf("Error drawing count img"),
			EXIT_FAILURE);
	if (put_overlay_img(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
