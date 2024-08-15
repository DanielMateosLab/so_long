/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:22:48 by damateos          #+#    #+#             */
/*   Updated: 2024/08/13 18:07:26 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*str_array_clear(char **table)
{
	size_t	i;

	if (!table)
		return (NULL);
	i = 0;
	while (table[i])
		ft_free((void **)&table[i++]);
	return (ft_free((void **)&table));
}

char	**str_array_resize(char **arr, size_t len, size_t new_len)
{
	char	**new_arr;
	size_t	i;

	new_arr = (char **)ft_calloc(new_len, sizeof(char *));
	if (!new_arr)
		return (str_array_clear(arr));
	i = 0;
	while (i < len && i < new_len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	while (i < len)
		ft_free((void **)&arr[i++]);
	ft_free((void **)&arr);
	return (new_arr);
}

size_t	str_array_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char	**str_array_copy(char **arr)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	i;

	if (!arr)
		return (NULL);
	arr_len = str_array_len(arr);
	new_arr = (char **)ft_calloc(arr_len + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (str_array_clear(new_arr));
		i++;
	}
	return (new_arr);
}

void	str_array_loop_char(char **arr,
	void (*fn)(char **arr, t_point pos, int *stop, void *), void *param)
{
	int	x;
	int	y;
	int	stop;

	y = 0;
	stop = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			fn(arr, (t_point){.x = x, .y = y}, &stop, param);
			if (stop)
				return ;
			x++;
		}
		y++;
	}
}
