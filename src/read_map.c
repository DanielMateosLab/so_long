/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:04:55 by damateos          #+#    #+#             */
/*   Updated: 2024/07/26 19:49:14 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_clear_str_arr(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
		ft_free((void **)&table[i++]);
	return (ft_free((void **)&table));
}

char	**ft_resize_str_arr(char **arr, size_t len, size_t new_len)
{
	char	**new_arr;
	size_t	i;

	new_arr = (char **)ft_calloc(new_len, sizeof(char *));
	if (!new_arr)
		return (ft_clear_str_arr(arr));
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

char	*get_next_line_without_nl(int fd)
{
	char	*temp_line;
	char	*res;
	size_t	len;

	temp_line = get_next_line(fd);
	len = ft_strlen(temp_line);
	if (temp_line && temp_line[len - 1] == '\n')
	{
		res = ft_substr(temp_line, 0, ft_strlen(temp_line) - 1);
		ft_free((void **)&temp_line);
		return (res);
	}
	return (temp_line);
}

char	**loop_map(size_t *_i, size_t *_lines, char **map, int fd)
{
	size_t	i;
	size_t	lines;

	i = *_i;
	lines = *_lines;
	map[i] = get_next_line_without_nl(fd);
	while (map[i++])
	{
		if (i == lines - 2)
		{
			map = ft_resize_str_arr(map, lines, lines + 20);
			lines += 20;
			if (!map)
				return (NULL);
		}
		map[i] = get_next_line_without_nl(fd);
	}
	*_i = i;
	*_lines = lines;
	return (map);
}

char	**read_map(const char *path)
{
	char	**map;
	int		fd;
	size_t	lines;
	size_t	i;

	lines = 20;
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_printf(PATH_ERR), NULL);
	map = (char **)ft_calloc(lines, sizeof(char *));
	if (!map)
		return (ft_printf(READ_MAP_ERR), NULL);
	loop_map(&i, &lines, map, fd);
	close(fd);
	if (i < lines - 2)
		map = ft_resize_str_arr(map, lines, i);
	return (map);
}
