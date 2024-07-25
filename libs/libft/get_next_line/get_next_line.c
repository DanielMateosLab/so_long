/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:05:00 by damateos          #+#    #+#             */
/*   Updated: 2024/07/25 19:51:00 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}

void	buff_to_line(char **line, char *buff)
{
	if (ft_strlen(buff) == 0)
	{
		resize_line(line, 0);
		return ;
	}
	resize_line(line, ft_strlen(buff));
	if (*line)
		ft_memcpy(*line, buff, ft_strlen(buff));
}

void	read_until_nl_eof(char **line, int fd)
{
	int		nl_index;
	int		bytes_read;
	size_t	len;

	nl_index = get_newline_i(*line);
	bytes_read = 1;
	while (nl_index == -1 && bytes_read != 0)
	{
		resize_line(line, (len = ft_strlen(*line)) + BUFFER_SIZE);
		if (!*line)
			return ;
		bytes_read = read(fd, *line + len, BUFFER_SIZE);
		if (bytes_read == -1 || (!bytes_read && !len))
		{
			if (*line)
			{
				free(*line);
				*line = NULL;
			}
			return ;
		}
		(*line)[len + bytes_read] = '\0';
		nl_index = get_newline_i(*line);
	}
}

char	*save_suffix_and_return_line(char *line, char *buff)
{
	int	line_end_i;

	line_end_i = get_newline_i(line);
	if (line_end_i == -1)
	{
		buff[0] = '\0';
		resize_line(&line, ft_strlen(line));
		return (line);
	}
	ft_strlcpy(buff, line + line_end_i + 1, ft_strlen(line) - line_end_i);
	line[line_end_i + 1] = '\0';
	resize_line(&line, line_end_i + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {'\0'};
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	buff_to_line(&line, buff);
	if (!line)
		return (NULL);
	read_until_nl_eof(&line, fd);
	if (!line)
	{
		buff[0] = '\0';
		return (NULL);
	}
	return (save_suffix_and_return_line(line, buff));
}
