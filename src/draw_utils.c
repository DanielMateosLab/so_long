/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:00:55 by damateos          #+#    #+#             */
/*   Updated: 2024/08/11 20:01:59 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_pixel_i(t_point point, t_point delta, int width)
{
	return (((point.y * BASE_TILE_SIZE + delta.y) * width
			+ (point.x * BASE_TILE_SIZE + delta.x)) * 4);
}

int	pseudo_random(int x, int y)
{
	return (x * 23 + y * 23 - y);
}
