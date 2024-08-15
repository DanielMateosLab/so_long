/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:00:55 by damateos          #+#    #+#             */
/*   Updated: 2024/08/15 17:10:32 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_pixel_i(t_point point, t_point delta, int width)
{
	return (((point.y * TILE_SIZE + delta.y) * width
			+ (point.x * TILE_SIZE + delta.x)) * 4);
}

int	pseudo_random(int x, int y)
{
	return (x * 23 + y * 23 - y);
}

void	draw_tile(mlx_image_t *dest, mlx_image_t *src,
		t_point src_p, t_point dst_p)
{
	t_point	dp;
	int		i;

	dp.y = 0;
	while (dp.y < TILE_SIZE)
	{
		dp.x = 0;
		while (dp.x < TILE_SIZE)
		{
			i = get_pixel_i(src_p, dp, src->width);
			mlx_put_pixel(dest, dst_p.x * TILE_SIZE + dp.x,
				dst_p.y * TILE_SIZE + dp.y,
				src->pixels[i] << 24 | src->pixels[i + 1] << 16
				| src->pixels[i + 2] << 8 | src->pixels[i + 3]);
			dp.x++;
		}
		dp.y++;
	}
}
