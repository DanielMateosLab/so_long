/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:22:48 by damateos          #+#    #+#             */
/*   Updated: 2024/07/27 18:28:47 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*str_array_clear(char **table)
{
	size_t	i;

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

char	**str_array_copy(char **arr)
{
// TODO: implement
}
